<?php

/**
 * Implements hook_views_data
 */

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function yql_views_query_views_data () 
{
    $data = array();
    
    $data['yql']['table']['group'] = t('YQL');

    $data['yql']['table']['base'] = array(
        'title' => t('YQL Query: Flexible'),
        'help' => t('Flexible querying from YQL endpoint.'),
        'query_id' => 'column',
    );

    $data['yql']['column'] = array(
        'title' => t('Column'),
        'help' => t('Add/filter the value of a column in the table.'),
        'field' => array(
            'title' => t('Column'),
            'id' => 'column',
        ),
        'filter' => array(
            'title' => t('Column'),
            'id' => 'column',
        ),
        'sort' => array(
            'title' => t('Column'),
            'id' => 'column',
        ),
        'argument' => array(
            'title' => t('Column'),
            'id' => 'column',
        ),
    );

    return $data;
}