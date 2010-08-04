<?php
// $Id$

/**
 * Implements hook_views_data
 */

function yql_views_query_views_data() {
  $data['yql']['table']['group'] = t('YQL');

  $data['yql']['table']['base'] = array(
    'title' => t('YQL Query: Flexible'),
    'help' => t('Flexible querying from YQL endpoint.'),
    'query class' => 'yql_query',
  );

  $data['yql']['column'] = array(
    'title' => t('Column'),
    'help' => t('Add/filter the value of a column in the table.'),
    'field' => array(
      'handler' => 'yql_views_query_handler_field_column',
    ),
    'filter' => array(
      'handler' => 'yql_views_query_handler_filter_column',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function yql_views_query_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'yql_views_query') . '/handlers',
    ),
    'handlers' => array(
      // Fields
      'yql_views_query_handler_field' => array(
        'parent' => 'views_handler_field',
      ),
      'yql_views_query_handler_field_column' => array(
        'parent' => 'yql_views_query_handler_field',
      ),

      // Filters
      'yql_views_query_handler_filter' => array(
        'parent' => 'views_handler_filter',
      ),
      'yql_views_query_handler_filter_column' => array(
        'parent' => 'yql_views_query_handler_filter',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function yql_views_query_views_plugins() {
  return array(
    'query' => array(
      'yql_query' => array(
        'title' => t('YQL Query'),
        'help' => t('Query will be generated and run using YQL.'),
        'handler' => 'yql_views_query_plugin_query_yql'
      ),
    ),
  );
}
