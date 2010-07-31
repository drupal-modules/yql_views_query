<?php
// $Id$

class yql_views_query_plugin_query_yql extends views_plugin_query {

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table = 'yql_ep', $base_field, $options) {
    parent::init($base_table, $base_field, $options);

    $this->api_url = $this->options['api_url'] ? $this->options['api_url'] : 'http://query.yahooapis.com/v1/public/yql';
    $this->api_method = $this->options['api_method'] ? $this->options['api_method'] : 'json';
    $this->yql_base_table = $this->options['yql_base_table'];
  }

  /**
   * Construct the "WHERE" or "HAVING" part of the query.
   *
   * @param $where
   *   'where' or 'having'.
   */
  function condition_query($where = 'where') {
    $clauses = array();
    foreach ($this->$where as $group => $info) {
      if (empty($info['clauses'])) {
        continue;
      }

      $clause = implode(") " . $info['type'] . " (", $info['clauses']);
      if (count($info['clauses']) > 1) {
        $clause = '(' . $clause . ')';
      }
      $clauses[] = $clause;
    }

    if ($clauses) {
      $keyword = drupal_strtoupper($where);
      if (count($clauses) > 1) {
        return "$keyword (" . implode(")\n    " . $this->group_operator . ' (', array_filter($clauses)) . ")\n";
      }
      else {
        return "$keyword " . array_shift($clauses) . "\n";
      }
    }
    return "";
  }

  function use_pager() {
    return FALSE;
  }

  /**
   * Generate a query and a countquery from all of the information supplied
   * to the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($view, $get_count = FALSE) {
/*
    $where = $this->condition_query();

    $params = $this->params;
    if (!empty($view->pager['items_per_page'])) {
      $params['rpp'] = $view->pager['items_per_page'] <= 100 ? $view->pager['items_per_page'] : 100;
    }
    $params['q'] = $where;

    // Build the full string.
    $items = array();
    if ($params) {
      foreach ($params as $key => $value) {
        if ($key == 'q') {
          array_unshift($items, 'q='. urlencode($value));
        }
        else {
          $items[] = $key .'='. urlencode($value);
        }
      }
    }
    $params = implode('&', $items);

    return $params;
*/
    $query = '';

    // Add the where clauses
    $where = $this->condition_query();

    // Add the field clauses
    $fields = '';
    $fields_array = $this->fields;
    foreach($fields_array as $alias => $field) {
      if (!empty($fields)) {
        $fields .= ', ';
      }
      $fields .= $field['field'];
    }
    // Add the base table
    $from = $this->yql_base_table;

    // Build the query string
    $query = "SELECT $fields FROM $from";
    if (!empty($where)) {
      $query = "$query $where";
    }

    // Add table definitions
    if (!empty($this->options['yql_custom_tables'])) {
      $query = $this->options['yql_custom_tables'] . $query;
    }
    return $query;
  }


  /**
   * Get the arguments attached to the WHERE and HAVING clauses of this query.
   */
  function get_where_args() {
    $args = array();
    foreach ($this->where as $group => $where) {
      $args = array_merge($args, $where['args']);
    }

    if ($this->having) {
      foreach ($this->having as $group => $having) {
        $args = array_merge($args, $having['args']);
      }
    }
    return $args;
  }

  function add_param($param, $value = '') {
    $this->params[$param] = $value;
  }

  function add_where($group, $clause) {
    $args = func_get_args();
    array_shift($args); // ditch $group
    array_shift($args); // ditch $clause

    // Expand an array of args if it came in.
    if (count($args) == 1 && is_array(reset($args))) {
      $args = current($args);
    }

    // Ensure all variants of 0 are actually 0. Thus '', 0 and NULL are all
    // the default group.
    if (empty($group)) {
      $group = 0;
    }

    // Check for a group.
    if (!isset($this->where[$group])) {
      $this->set_where_group('AND', $group);
    }

    // Add the clause and the args.
    if (is_array($args)) {
      $this->where[$group]['clauses'][] = $clause;
      // we use array_values() here to prevent array_merge errors as keys from multiple
      // sources occasionally collide.
      $this->where[$group]['args'] = array_merge($this->where[$group]['args'], array_values($args));
    }
  }

  /**
   * Let modules modify the query just prior to finalizing it.
   */
  function alter(&$view) {
    foreach (module_implements('twitter_views_query_alter') as $module) {
      $function = $module . '_twitter_views_query_alter';
      $function($view, $this);
    }
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $this->init_pager($view);
    if ($this->pager->use_pager()) {
      $this->pager->set_current_page($view->current_page);
    }

    $view->build_info['query'] = $this->query($view);
    //$view->build_info['count_query'] = $this->query($view, TRUE);
    $view->build_info['count_query'] = 10;
    $view->build_info['query_args'] = $this->get_where_args();
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  function execute(&$view) {
    $query = $view->build_info['query'];

    if ($query) {
      $replacements = module_invoke_all('views_query_substitutions', $view);
      $query = str_replace(array_keys($replacements), $replacements, $query);

      // Encode the query into URL friendly format
      $query = urlencode($query);
      $format_string = $this->api_method == 'json' ? '&format=json' : '&format=xml';
      $url = $this->api_url .'?q='. $query . $format_string;

      $start = views_microtime();

      $results = drupal_http_request($url, array(), 'GET');

      // @todo fix the failure detection
      /*
      if (_twitter_request_failure($results)) {
        return FALSE;
      }
      */

      switch ($this->api_method) {
        case 'xml':
          // Not supported yet.
          return;
        case 'json':
        default:
          $results = json_decode($results->data, TRUE);
          break;
      }

      if ($results['query']['results']) {
        // If the base object is specified, use that. Otherwise use the first object.
        if (!empty($this->options['yql_base_object']) && isset($results['query']['results'][$this->options['yql_base_object']])) {
          $result_array = $results['query']['results'][$this->options['yql_base_object']];
        }
        else {
          $result_array = current($results['query']['results']);
        }

        $view->result = $result_array;

        foreach ($view->result as $key => $value) {
          $view->result[$key] = (object) $value;
        }

        // Save the metadata into the object
        unset($results['query']['results']);
        foreach ($results as $key => $value) {
          $this->$key = $value;
        }

        $this->execute_time = $this->completed_in;
        $this->items_per_page = $this->results_per_page;

        // FIXME
        //$this->total_rows = $this->results_per_page * 2;
        //$this->pager['current_page'] = $this->page -1;
      }
    }
//dpm($url);
    $view->execute_time = views_microtime() - $start;
  }

  function add_signature(&$view) {
    //$view->query->add_field(NULL, "'" . $view->name . ':' . $view->current_display . "'", 'view_name');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['api_url'] = array('default' => 'http://query.yahooapis.com/v1/public/yql');
    $options['api_method'] = array('default' => 'json');
    $options['yql_base_table'] = array('default' => '');
    $options['yql_custom_table'] = array('default' => '');
    $options['yql_base_object'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['api_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate API URL'),
      '#default_value' => $this->options['api_url'],
      '#description' => t("The URL YQL will be queried from (default: Yahoo! YQL Engine)."),
      '#required' => TRUE,
    );

    $form['api_method'] = array(
      '#type' => 'select',
      '#title' => t('API method'),
      '#description' => t("The format of the data returned by YQL."),
      '#default_value' => 'json',
      '#options' => array(
        'json' => 'JSON',
      ),
      '#required' => TRUE,
    );

    $form['yql_base_table'] = array(
      '#type' => 'textfield',
      '#title' => t('YQL base table'),
      '#default_value' => $this->options['yql_base_table'],
      '#description' => t("A base table that view will be querying by using YQL to. Example: flickr.photos.recent"),
      '#required' => TRUE,
    );

    // @todo: add validation for custom open table.
    $form['yql_custom_tables'] = array(
      '#type' => 'textarea',
      '#title' => t('Custom open tables.'),
      '#default_value' => $this->options['yql_custom_tables'],
      '#description' => t("Add custom table into the YQL Query.<br/>Example:" . 'USE \'http://www.datatables.org/delicious/delicious.feeds.popular.xml\' AS delicious.feeds.popular;'),
    );

    $form['yql_base_object'] = array(
      '#type' => 'textfield',
      '#title' => t('YQL base object'),
      '#default_value' => $this->options['yql_base_object'],
      '#description' => t('The base object YQL will be querying from. If this is left empty, the first object in the result set will be taken as the base object'),
    );
  }

  /**
   * Add a field to the query table, possibly with an alias. This will
   * automatically call ensure_table to make sure the required table
   * exists, *unless* $table is unset.
   *
   * @param $table
   *   The table this field is attached to. If NULL, it is assumed this will
   *   be a formula; otherwise, ensure_table is used to make sure the
   *   table exists.
   * @param $field
   *   The name of the field to add. This may be a real field or a formula.
   * @param $alias
   *   The alias to create. If not specified, the alias will be $table_$field
   *   unless $table is NULL. When adding formulae, it is recommended that an
   *   alias be used.
   * @param $params
   *   An array of parameters additional to the field that will control items
   *   such as aggregation functions and DISTINCT.
   *
   * @return $name
   *   The name that this field can be referred to as. Usually this is the alias.
   */
  function add_field($table, $field, $alias = '', $params = array()) {
    // We can't use any alias in YQL query, so just use the real field name.
    $alias = $field;

    // Create a field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
    ) + $params;

    if (empty($this->fields[$alias])) {
      $this->fields[$alias] = $field_info;
    }

    return $alias;

    /*
    // We check for this specifically because it gets a special alias.
    if ($table == $this->base_table && $field == $this->base_field && empty($alias)) {
      $alias = $this->base_field;
    }

    if ($table && empty($this->table_queue[$table])) {
      $this->ensure_table($table);
    }

    if (!$alias && $table) {
      $alias = $table . '_' . $field;
    }

    // Make sure an alias is assigned
    $alias = $alias ? $alias : $field;

    // PostgreSQL truncates aliases to 63 characters: http://drupal.org/node/571548

    // We limit the length of the original alias up to 60 characters
    // to get a unique alias later if its have duplicates
    $alias = substr($alias, 0, 60);

    // Create a field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
    ) + $params;

    // Test to see if the field is actually the same or not. Due to
    // differing parameters changing the aggregation function, we need
    // to do some automatic alias collision detection:
    $base = $alias;
    $counter = 0;
    while (!empty($this->fields[$alias]) && $this->fields[$alias] != $field_info) {
      $field_info['alias'] = $alias = $base . '_' . ++$counter;
    }

    if (empty($this->fields[$alias])) {
      $this->fields[$alias] = $field_info;
    }

    return $alias;
    */
  }
}
