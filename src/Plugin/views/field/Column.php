<?php

namespace Drupal\yql_views_query\Plugin\views\field;

use Drupal\views\Annotation\ViewsField;
use Drupal\views\Plugin\views\field\FieldPluginBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\views\ResultRow;

/**
 * Field handler for search snippet.
 *
 * @ingroup views_field_handlers
 *
 * @ViewsField("column")
 */
class Column extends FieldPluginBase 
{
    /**
     * Constructor; calls to base object constructor.
     */
    function construct() 
    {
        parent::construct();
        $this->format = isset($this->definition['format']) ? $this->format : NULL;

        $this->additional_fields = array();
        
        if (is_array($this->format)) 
        {
            $this->additional_fields['format'] = $this->format;
        }
    }

    function render(ResultRow $values) 
    {
        $field_names = explode('.', $this->field_alias);
        $value = (array) $values;
        
        while ($key = array_shift($field_names)) 
        {
            $value = $value[$key];
        }
        
        $value = is_string($value) ? $value : $value['content'];
        $format = isset($this->format) ? $this->format : filter_fallback_format();
        
        return check_markup($value, $format);
    }

    function elementType($none_supported = FALSE, $default_empty = FALSE, $inline = FALSE) 
    {
        if (isset($this->definition['element type'])) 
        {
            return $this->definition['element type'];
        }

        return 'div';
    }

    function defineOptions() 
    {
        $options = parent::defineOptions();
        $options['field_name'] = array('default' => '');
        return $options;
    }
    
    function buildOptionsForm(&$form, FormStateInterface $form_state) 
    {
        parent::buildOptionsForm($form, $form_state);
        
        $form['field_name'] = array(
            '#title' => $this->t('Field name'),
            '#description' => t('The field name that wants to be included into the view. Example: Rating.AverageRating'),
            '#type' => 'textfield',
            '#default_value' => $this->options['field_name'],
            '#required' => TRUE,
        );                
    }
    
    /**
     * Called to add the field to a query.
     */
    function query() 
    {
        $this->field_alias = $this->query->add_field($this->tableAlias, $this->options['field_name']);
        $this->addAdditionalFields();
    }

    /**
     * Provide extra data to the administration form
     */
    function adminSummary() 
    {
        return $this->label();
    }
}
