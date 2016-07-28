<?php

namespace Drupal\yql_views_query\Plugin\views\filter;

use Drupal\views\Annotation\ViewsFilter;
use Drupal\views\Plugin\views\filter\FilterPluginBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Component\Utility\SafeMarkup;
/**
 * Field handler for search snippet.
 *
 * @ingroup views_filter_handlers
 *
 * @ViewsFilter("column")
 */
class Column extends FilterPluginBase 
{
    var $no_single = TRUE;

    function defineOptions() 
    {
        $options = parent::defineOptions();

        $options['case'] = array('default' => TRUE);
        $options['field_name'] = array('default' => '');

        return $options;
    }

    function operators() 
    {
        $operators = array(
            '=' => array(
                'title' => t('Is equal to'),
                'short' => t('='),
                'method' => 'op_equal',
                'values' => 1,
            ),
            '!=' => array(
                'title' => t('Is not equal to'),
                'short' => t('!='),
                'method' => 'op_equal',
                'values' => 1,
            ),
            'contains' => array(
                'title' => t('Contains'),
                'short' => t('contains'),
                'method' => 'op_contains',
                'values' => 1,
            ),
            'word' => array(
                'title' => t('Contains any word'),
                'short' => t('has word'),
                'method' => 'op_word',
                'values' => 1,
            ),
            'allwords' => array(
                'title' => t('Contains all words'),
                'short' => t('has all'),
                'method' => 'op_word',
                'values' => 1,
            ),
            'starts' => array(
                'title' => t('Starts with'),
                'short' => t('begins'),
                'method' => 'op_starts',
                'values' => 1,
            ),
            'not_starts' => array(
                'title' => t('Does not start with'),
                'short' => t('not_begins'),
                'method' => 'op_not_starts',
                'values' => 1,
            ),
            'ends' => array(
                'title' => t('Ends with'),
                'short' => t('ends'),
                'method' => 'op_ends',
                'values' => 1,
            ),
            'not_ends' => array(
                'title' => t('Does not end with'),
                'short' => t('not_ends'),
                'method' => 'op_not_ends',
                'values' => 1,
            ),
            'not' => array(
                'title' => t('Does not contain'),
                'short' => t('!has'),
                'method' => 'op_not',
                'values' => 1,
            ),
            'shorterthan' => array(
                'title' => t('Length is shorter than'),
                'short' => t('shorter than'),
                'method' => 'op_shorter',
                'values' => 1,
            ),
            'longerthan' => array(
                'title' => t('Length is longer than'),
                'short' => t('longer than'),
                'method' => 'op_longer',
                'values' => 1,
            ),
        );
        // if the definition allows for the empty operator, add it.
        if (!empty($this->definition['allow empty'])) {
            $operators += array(
                'empty' => array(
                  'title' => t('Is empty (NULL)'),
                  'method' => 'op_empty',
                  'short' => t('empty'),
                  'values' => 0,
                ),
                'not empty' => array(
                  'title' => t('Is not empty (NOT NULL)'),
                  'method' => 'op_empty',
                  'short' => t('not empty'),
                  'values' => 0,
                ),
            );
        }

        return $operators;
    }

    /**
     * Build strings from the operators() for 'select' options
     */
    function operatorOptions($which = 'title') 
    {
        $options = array();
        foreach ($this->operators() as $id => $info) 
        {
            $options[$id] = $info[$which];
        }

        return $options;
    }

    function adminSummary() 
    {
      $output = SafeMarkup::checkPlain($this->options['field_name']);

        if (!empty($this->options['exposed'])) 
        {
            return $output . ', ' . t('exposed');
        }

        $options = $this->operatorOptions('short');
        $output = $output . ' ' . SafeMarkup::checkPlain($options[$this->operator]);
        if (in_array($this->operator, $this->operator_values(1))) 
        {
            $output .= ' ' . SafeMarkup::checkPlain($this->value);
        }
        return $output;
    }

    public function buildOptionsForm(&$form, FormStateInterface $form_state) 
    {
        parent::buildOptionsForm($form, $form_state);
        
        $form['case'] = array(
            '#type' => 'checkbox',
            '#title' => t('Case sensitive'),
            '#default_value' => $this->options['case'],
            '#description' => t('Case sensitive filters may be faster. MySQL might ignore case sensitivity.'),
        );

        $form['field_name'] = array(
            '#type' => 'textfield',
            '#title' => 'Field name',
            '#description' => t('The field name in the table that will be used as the filter.'),
            '#default_value' => $this->options['field_name'],
            '#required' => TRUE,
        );
    }

    function operator_values($values = 1) 
    {
      $options = array();
        foreach ($this->operators() as $id => $info) 
        {
            if (isset($info['values']) && $info['values'] == $values) 
            {
              $options[] = $id;
            }
        }

        return $options;
    }

    /**
     * Provide a simple textfield for equality
     */
    protected function valueForm(&$form, FormStateInterface $form_state)
    {       
        $form['value'] = array(
            '#type' => 'textfield',
            '#title' => t('Value'),
            '#size' => 30
        );           
    }

    /**
     * Add this filter to the query.
     *
     * Due to the nature of fapi, the value and the operator have an unintended
     * level of indirection. You will find them in $this->operator
     * and $this->value respectively.
     */
    function query() 
    {
        //$this->ensure_my_table();
        $field = $this->options['field_name'];

        $info = $this->operators();
        if (!empty($info[$this->operator]['method'])) 
        {
            $this->{$info[$this->operator]['method']}($field);
        }
    }

    function op_equal($field) 
    {
        // operator is either = or !=
        $value = is_array($this->value) ? $this->value[0] : $this->value;
        $this->query->add_where($this->options['group'], "$field $this->operator '$value'", $field, $this->value);
    }

    function op_contains($field) 
    {
        $this->query->add_where($this->options['group'], "$field LIKE '%%$this->value%%'", $field, $this->value);
    }

    function op_word($field) {
        $where = array();
        preg_match_all('/ (-?)("[^"]+"|[^" ]+)/i', ' ' . $this->value, $matches, PREG_SET_ORDER);
        foreach ($matches as $match) 
        {
            $phrase = false;
            // Strip off phrase quotes
            if ($match[2]{0} == '"') 
            {
                $match[2] = substr($match[2], 1, -1);
                $phrase = true;
            }
            $words = trim($match[2], ',?!();:-');
            $words = $phrase ? array($words) : preg_split('/ /', $words, -1, PREG_SPLIT_NO_EMPTY);
            foreach ($words as $word) 
            {
                $where[] = "$field LIKE '%%$word%%'";
                $values[] = $field;
                $values[] = trim($word, " ,!?");
            }
        }

        if (!$where) 
        {
            return;
        }

        if ($this->operator == 'word') 
        {
            $where = '(' . implode(' OR ', $where) . ')';
        }
        else 
        {
            $where = implode(' AND ', $where);
        }
        // previously this was a call_user_func_array but that's unnecessary
        // as views will unpack an array that is a single arg.
        $this->query->add_where($this->options['group'], $where, $values);
    }

    function op_starts($field) 
    {
        $this->query->add_where($this->options['group'], "$field LIKE '$this->value%%'", $field, $this->value);
    }

    function op_not_starts($field) 
    {
        $this->query->add_where($this->options['group'], "$field NOT LIKE '$this->value%%'", $field, $this->value);
    }

    function op_ends($field) 
    {
        $this->query->add_where($this->options['group'], "$field LIKE '%%$this->value'", $field, $this->value);
    }

    function op_not_ends($field) 
    {
        $this->query->add_where($this->options['group'], "$field NOT LIKE '%%$this->value'", $field, $this->value);
    }

    function op_not($field) 
    {
        $this->query->add_where($this->options['group'], "$field NOT LIKE '%%$this->value%%'", $field, $this->value);
    }

    function op_empty($field) 
    {
        if ($this->operator == 'empty') 
        {
            $operator = "IS NULL";
        }
        else 
        {
            $operator = "IS NOT NULL";
        }

        $this->query->add_where($this->options['group'], "$field $operator");
    }
}
