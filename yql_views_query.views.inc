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
        'query_id' => 'yql_views_query_handler_query_column',
    );

    $data['yql']['column'] = array(
        'title' => t('Column'),
        'help' => t('Add/filter the value of a column in the table.'),
        'field' => array(
            'title' => t('YQL'),
            'id' => 'yql_views_query_handler_field_column',
        ),
        'filter' => array(
            'title' => t('YQL'),
            'id' => 'yql_views_query_handler_filter_column',
        ),
        'sort' => array(
            'title' => t('YQL'),
            'id' => 'yql_views_query_handler_sort_column',
        ),
        'argument' => array(
            'title' => t('YQL'),
            'id' => 'yql_views_query_handler_argument_column',
        ),
        'query' => array(
            'title' => t('YQL Query'),
            'help' => t('Query will be generated and run using YQL.'),
            'id' => 'yql_views_query_handler_query_column',
        ),
    );

    return $data;
}