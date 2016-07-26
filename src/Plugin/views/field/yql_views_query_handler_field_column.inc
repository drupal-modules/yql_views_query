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
 * @ViewsField("yql_views_query_handler_field_column")
 */
class Yql_views_query_handler_field_column extends FieldPluginBase 
{
    function defineOptions () 
    {
        $options = parent::defineOptions();
        $options['field_name'] = array('default' => '');
        
        return $options;
    }

    function buildOptionsForm(&$form, FormStateInterface $form_state) 
    {
        $form['field_name'] = array(
          '#title' => $this->t('Field name'),
          '#description' => t('The field name that wants to be included into the view. Example: Rating.AverageRating'),
          '#type' => 'textfield',
          '#default_value' => $this->options['field_name'],
          '#required' => TRUE,
        );
        
        parent::buildOptionsForm($form, $form_state);
    }
}
