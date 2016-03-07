<?php

class yql_views_query_handler_field_column extends yql_views_query_handler_field {

  /**
   * Constructor; calls to base object constructor.
   */
  function construct() {
    parent::construct();
    $this->format = isset($this->definition['format']) ? $this->format : NULL;

    $this->additional_fields = array();
    if (is_array($this->format)) {
      $this->additional_fields['format'] = $this->format;
    }
  }

  function render($values) {
    // Parse YQL result and output the appropriate value.
    $field_names = explode('.', $this->field_alias);
    // Traverse into multi-leveled array to get value based on array of key names.
    // Credits: http://stackoverflow.com/q/28616752/55075
    $value = (array)$values;
    while ($key = array_shift($field_names)) {
      $value = $value[$key];
    }
    $value = is_string($value) ? $value : $value['content'];
    $format = isset($this->format) ? $this->format : filter_fallback_format();
    //if ($value) {
    return check_markup($value, $format);
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
