<?php
/**
 * @file
 * directnews.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function directnews_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_node_info().
 */
function directnews_node_info() {
  $items = array(
    'directnewsfeed' => array(
      'name' => t('DirectnewsFeed'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
