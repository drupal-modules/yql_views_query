<?php
// $Id$
/**
 * Implementation of hook_views_default_views().
 */
function yql_views_query_views_default_views() {
  /*
   * View 'yql_test_1'
   */
  $view = new view;
  $view->name = 'yql_test_1';
  $view->description = 'A sample on what YQL query backend can do.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = 3.0-alpha1;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
/* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'local.search';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'column' => 'column',
    'column_1' => 'column_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'column' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_1' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column']['id'] = 'column';
  $handler->display->display_options['fields']['column']['table'] = 'yql';
  $handler->display->display_options['fields']['column']['field'] = 'column';
  $handler->display->display_options['fields']['column']['label'] = 'Title';
  $handler->display->display_options['fields']['column']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column']['field_name'] = 'Title';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_2']['id'] = 'column_2';
  $handler->display->display_options['fields']['column_2']['table'] = 'yql';
  $handler->display->display_options['fields']['column_2']['field'] = 'column';
  $handler->display->display_options['fields']['column_2']['label'] = 'Address';
  $handler->display->display_options['fields']['column_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_2']['field_name'] = 'Address';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_1']['id'] = 'column_1';
  $handler->display->display_options['fields']['column_1']['table'] = 'yql';
  $handler->display->display_options['fields']['column_1']['field'] = 'column';
  $handler->display->display_options['fields']['column_1']['label'] = 'Rating.AverageRating';
  $handler->display->display_options['fields']['column_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_1']['field_name'] = 'Rating.AverageRating';
  /* Sort criterion: YQL: Column */
  $handler->display->display_options['sorts']['column']['id'] = 'column';
  $handler->display->display_options['sorts']['column']['table'] = 'yql';
  $handler->display->display_options['sorts']['column']['field'] = 'column';
  $handler->display->display_options['sorts']['column']['order'] = 'DESC';
  $handler->display->display_options['sorts']['column']['field_name'] = 'Rating.AverageRating';
  /* Filter: YQL: Column */
  $handler->display->display_options['filters']['column']['id'] = 'column';
  $handler->display->display_options['filters']['column']['table'] = 'yql';
  $handler->display->display_options['filters']['column']['field'] = 'column';
  $handler->display->display_options['filters']['column']['value'] = 'sushi';
  $handler->display->display_options['filters']['column']['case'] = 1;
  $handler->display->display_options['filters']['column']['field_name'] = 'query';
  /* Filter: YQL: Column */
  $handler->display->display_options['filters']['column_1']['id'] = 'column_1';
  $handler->display->display_options['filters']['column_1']['table'] = 'yql';
  $handler->display->display_options['filters']['column_1']['field'] = 'column';
  $handler->display->display_options['filters']['column_1']['value'] = 'san fransisco, ca';
  $handler->display->display_options['filters']['column_1']['case'] = 1;
  $handler->display->display_options['filters']['column_1']['field_name'] = 'location';
  
/* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'yql_test_1';
  $views[$view->name] = $view;

  return $views;
}
