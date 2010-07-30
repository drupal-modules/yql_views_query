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
    $this->yql_base = $this->options['yql_base'];
    $this->yql_custom_tables = $this->options['yql_custom_tables'];
  }

  /**
   * Construct the "WHERE" or "HAVING" part of the query.
   *
   * @param $where
   *   'where' or 'having'.
   */
  function condition_query($where = 'where') {
    $clauses = array();
    if ($this->$where) {
      foreach ($this->$where as $group => $info) {
        $clause = implode($info['type'], $info['clauses']);
        if (count($info['clauses']) > 1) {
          $clause = $clause;
        }
        $clauses[] = $clause;
      }

      if ($clauses) {
        if (count($clauses) > 1) {
          return implode(")" . $this->group_operator , $clauses);
        }
        else {
          return array_shift($clauses);
        }
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

    // @todo add the where clauses
    $where = '';
    
    // @todo add the field clauses
    $fields = '*';    

    $from = $this->options['yql_base'];

    $query = 'SELECT ' . $fields . ' FROM ' . $from;
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

  /**
   * Create a new grouping for the WHERE or HAVING clause.
   *
   * @param $type
   *   Either 'AND' or 'OR'. All items within this group will be added
   *   to the WHERE clause with this logical operator.
   * @param $group
   *   An ID to use for this group. If unspecified, an ID will be generated.
   * @param $where
   *   'where' or 'having'.
   *
   * @return $group
   *   The group ID generated.
   */
  function set_where_group($type = 'AND', $group = NULL, $where = 'where') {
    // Set an alias.
    $groups = &$this->$where;

    if (!isset($group)) {
      $group = empty($groups) ? 1 : max(array_keys($groups)) + 1;
    }

    if ($type === 'AND') {
      $type = ' ';
    }

    // Create an empty group
    if (empty($groups[$group])) {
      $groups[$group] = array('clauses' => array(), 'args' => array());
    }

    $groups[$group]['type'] = strtoupper($type);
    return $group;
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
            
      if ($results['query']['results']['Artist']) {
        $view->result = $results['query']['results']['Artist'];

        // Save the metadata into the object
        unset($results['results']);
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

    $view->execute_time = views_microtime() - $start;    
  }

  function add_signature(&$view) {
    //$view->query->add_field(NULL, "'" . $view->name . ':' . $view->current_display . "'", 'view_name');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['api_url'] = array('default' => 'http://query.yahooapis.com/v1/public/yql');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['api_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate API URL'),
      '#default_value' => $this->options['api_url'],
      '#description' => t("The URL YQL will be queried from (default: Yahoo! YQL Engine).",
      array('!identica' => l('Identi.ca', 'http://laconi.ca/trac/wiki/TwitterCompatibleAPI'))),
    );
    
    $form['api_method'] = array(
      '#type' => 'select',
      '#title' => t('API Method'),
      '#description' => t("The format of the data returned by YQL."),
      '#default_value' => 'json',
      '#options' => array(
        'json' => 'JSON',
      ),
    );
    
    $form['yql_base'] = array(
      '#type' => 'textfield',
      '#title' => t('The base table YQL will be querying from.'),
      '#default_value' => $this->options['yql_base'],
      '#description' => t("A base table that view will be querying by using YQL to. Example: flickr.photos.recent"),
    );
    
    // @todo: add validation for custom open table.
    $form['yql_custom_tables'] = array(
      '#type' => 'textarea',
      '#title' => t('Custom open tables.'),
      '#default_value' => $this->options['yql_custom_tables'],
      '#description' => t("Add custom table into the YQL Query. Format is the same as specified in YQL: USE (url) as (alias);"),
    );
  }
}