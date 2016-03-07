<?php
/**
 * Implementation of hook_views_default_views().
 */
function yql_views_query_views_default_views() {
  /*
   * View 'yql_flickr_photos_recent'
   */
  $view = new view;
  $view->name = 'yql_flickr_photos_recent';
  $view->description = 'YQL Example: List out the latest photos from Flickr with YQL';
  $view->tag = 'YQL demo';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = 3.0-alpha1;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['api_url'] = '';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'flickr.photos.recent';
  $handler->display->display_options['query']['options']['num_items'] = '10';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'column' => 'column',
    'column_2' => 'column_2',
    'column_1' => 'column_1',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'column' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_2' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_1' => array(
      'align' => '',
      'separator' => '',
    ),
    'nothing' => array(
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
  $handler->display->display_options['fields']['column']['label'] = 'title';
  $handler->display->display_options['fields']['column']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column']['field_name'] = 'title';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_2']['id'] = 'column_2';
  $handler->display->display_options['fields']['column_2']['table'] = 'yql';
  $handler->display->display_options['fields']['column_2']['field'] = 'column';
  $handler->display->display_options['fields']['column_2']['label'] = 'owner';
  $handler->display->display_options['fields']['column_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_2']['field_name'] = 'owner';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_1']['id'] = 'column_1';
  $handler->display->display_options['fields']['column_1']['table'] = 'yql';
  $handler->display->display_options['fields']['column_1']['field'] = 'column';
  $handler->display->display_options['fields']['column_1']['label'] = 'id';
  $handler->display->display_options['fields']['column_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_1']['field_name'] = 'id';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'See in Flickr';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Link';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'http://flickr.com/photos/[column_2]/[column_1]/';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;

/* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'yql_flickr_photos_recent';
  $views[$view->name] = $view;

  /*
   * View 'yql_sushi'
   */
  $view = new view;
  $view->name = 'yql_sushi';
  $view->description = 'YQL Example: List out sushi restaurant in a location with YQL';
  $view->tag = 'YQL demo';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = 3.0-alpha1;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['api_url'] = '';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'local.search';
  $handler->display->display_options['query']['options']['num_items'] = '30';
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
  $handler->display->display_options['filters']['column_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['column_1']['expose']['operator'] = 'column_1_op';
  $handler->display->display_options['filters']['column_1']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['column_1']['expose']['use_operator'] = 0;
  $handler->display->display_options['filters']['column_1']['expose']['identifier'] = 'column_1';
  $handler->display->display_options['filters']['column_1']['case'] = 1;
  $handler->display->display_options['filters']['column_1']['field_name'] = 'location';

/* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'yql_sushi';
  $views[$view->name] = $view;


  /*
   * View 'yql_tables'
   */
  $view = new view;
  $view->name = 'yql_tables';
  $view->description = 'YQL Example: A demonstration list with some tables accessible with YQL, and some help text';
  $view->tag = 'YQL demo';
  $view->view_php = '';
  $view->base_table = 'yql';
  $view->is_cacheable = FALSE;
  $view->api_version = '3.0-alpha1';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: YQL tables */
  $handler = $view->new_display('default', 'YQL tables', 'default');
  $handler->display->display_options['title'] = 'Example YQL Views page';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['api_url'] = '';
  $handler->display->display_options['query']['options']['yql_base_table'] = 'yql.tables';
  $handler->display->display_options['query']['options']['num_items'] = '50';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'counter' => 'counter',
    'column_3' => 'column_3',
    'column' => 'column',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'counter' => array(
      'align' => '',
      'separator' => '',
    ),
    'column_3' => array(
      'align' => '',
      'separator' => '',
    ),
    'column' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Help text';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'This view displays the first 50 of the tables available with Yahoo! Query Language. The full list can be viewed in <a href="http://developer.yahoo.com/yql/console/?env=http://datatables.org/alltables.env">the YQL Console at the Yahoo! Developer Network</a>.';
  $handler->display->display_options['header']['area']['format'] = '1';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'More help text';
  $handler->display->display_options['footer']['area']['empty'] = TRUE;
  $handler->display->display_options['footer']['area']['content'] = 'Note that many YQL statements use different source tables than the default YQL table. These source tables can be viewed in <a href="http://developer.yahoo.com/yql/console/?env=http://datatables.org/alltables.env">the YQL console at the Yahoo! developer network</a>. Any non-standard source table should be entered in the <em>query settings</em> (under <em>advanced settings</em>) using the form <strong>USE \'http://www.datatables.org/arxiv/arxiv.search.xml\' AS arxiv.search;</strong>.

  Any queries should be added as filters, on the form <strong>where <em>field name</em> = <em>value</em></strong>.';
  $handler->display->display_options['footer']['area']['format'] = '1';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column']['id'] = 'column';
  $handler->display->display_options['fields']['column']['table'] = 'yql';
  $handler->display->display_options['fields']['column']['field'] = 'column';
  $handler->display->display_options['fields']['column']['label'] = 'Table name';
  $handler->display->display_options['fields']['column']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column']['field_name'] = 'name';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_1']['id'] = 'column_1';
  $handler->display->display_options['fields']['column_1']['table'] = 'yql';
  $handler->display->display_options['fields']['column_1']['field'] = 'column';
  $handler->display->display_options['fields']['column_1']['label'] = 'Access';
  $handler->display->display_options['fields']['column_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_1']['field_name'] = 'security';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_2']['id'] = 'column_2';
  $handler->display->display_options['fields']['column_2']['table'] = 'yql';
  $handler->display->display_options['fields']['column_2']['field'] = 'column';
  $handler->display->display_options['fields']['column_2']['label'] = '';
  $handler->display->display_options['fields']['column_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['column_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_2']['field_name'] = 'meta.documentation';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_3']['id'] = 'column_3';
  $handler->display->display_options['fields']['column_3']['table'] = 'yql';
  $handler->display->display_options['fields']['column_3']['field'] = 'column';
  $handler->display->display_options['fields']['column_3']['label'] = '';
  $handler->display->display_options['fields']['column_3']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['column_3']['alter']['text'] = 'Description: [column_3]<br />
  Documentation link: [column_2]';
  $handler->display->display_options['fields']['column_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_3']['field_name'] = 'description';
  /* Field: YQL: Column */
  $handler->display->display_options['fields']['column_4']['id'] = 'column_4';
  $handler->display->display_options['fields']['column_4']['table'] = 'yql';
  $handler->display->display_options['fields']['column_4']['field'] = 'column';
  $handler->display->display_options['fields']['column_4']['label'] = 'Sample query';
  $handler->display->display_options['fields']['column_4']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['column_4']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['column_4']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['column_4']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['column_4']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['column_4']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['column_4']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['column_4']['alter']['html'] = 0;
  $handler->display->display_options['fields']['column_4']['hide_empty'] = 0;
  $handler->display->display_options['fields']['column_4']['empty_zero'] = 0;
  $handler->display->display_options['fields']['column_4']['field_name'] = 'sampleQuery';

  /* Display: YQL tables (Page) */
  $handler = $view->new_display('page', 'YQL tables (Page)', 'page_1');
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['path'] = 'yql_tables';
  $views[$view->name] = $view;

  return $views;
}
