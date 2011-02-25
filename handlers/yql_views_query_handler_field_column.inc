<?php

class yql_views_query_handler_field_column extends yql_views_query_handler_field {

  /**
   * Constructor; calls to base object constructor.
   */
  function construct() {
    parent::construct();

    $this->format = $this->definition['format'] ? $this->definition['format'] : FILTER_FORMAT_DEFAULT;

    $this->additional_fields = array();
    if (!is_numeric($this->format)) {
      $this->additional_fields['format'] = array('field' => $this->format);
    }
  }

  function render($values) {
    // Traverse into multi-leveled result that YQL returns (in $values) and output the appropriate value.
    $field_names = explode('.', $this->field_alias);
    $field = array_shift($field_names);
    $value = $values->$field;
    foreach($field_names as $field) {
      if (is_array($value)) {
        $value = $value[$field];
      }
    }

    $format = is_numeric($this->format) ? $this->format : $values->{$this->aliases['format']};
    //if ($value) {
      return check_markup($value, $format, FALSE);
    //}
  }

  function element_type() {
    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }

    return 'div';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['field_name'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['field_name'] = array(
      '#title' => t('Field name'),
      '#description' => t('The field name that wants to be included into the view. Example: Rating.AverageRating'),
      '#type' => 'textfield',
      '#default_value' => $this->options['field_name'],
      '#required' => TRUE,
    );
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    //$this->ensure_my_table();
    // Add the field.
    $this->field_alias = $this->query->add_field($this->table_alias, $this->options['field_name']);
    $this->add_additional_fields();
  }

  /**
   * Provide extra data to the administration form
   */
  function admin_summary() {
    return $this->label();
  }
}
