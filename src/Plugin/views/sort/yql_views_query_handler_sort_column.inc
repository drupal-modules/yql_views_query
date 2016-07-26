<?php

namespace Drupal\yql_views_query\Plugin\views\sort;

use Drupal\views\Annotation\ViewsSort;
use Drupal\views\Plugin\views\sort\SortPluginBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Field handler for search snippet.
 *
 * @ingroup views_sort_handlers
 *
 * @ViewsSort("yql_views_query_handler_sort_column")
 */
class yql_views_query_handler_sort_column extends SortPluginBase 
{
    function defineOptions() 
    {
      $options = parent::defineOptions();

      $options['field_name'] = array('default' => '');

      return $options;
    }

    function buildOptionsForm(&$form, FormStateInterface &$form_state) 
    {
        parent::buildOptionsForm($form, $form_state);

        $form['field_name'] = array(
            '#type' => 'textfield',
            '#title' => t('Field name'),
            '#description' => t('The field name that the sorting will be done from. NOTE: Only the first field name in the sort handler that will be taken for sorting.'),
            '#default_value' => $this->options['field_name'],
            '#required' => TRUE,
        );
    }

    function query() 
    {
        $this->query->add_orderby($this->table_alias, $this->options['field_name'], $this->options['order']);
    }

    function adminSummary() 
    {
        $field = $this->options['field_name'];

        if (!empty($this->options['exposed'])) 
        {
            return $field . ' ' . t('Exposed');
        }
        
        switch ($this->options['order']) 
        {
            case 'ASC':
            case 'asc':
            default:
                return $field . ' ' . t('asc');
            break;
            case 'DESC':
            case 'desc':
                return $field . ' ' . t('desc');
            break;
        }
    }
}
