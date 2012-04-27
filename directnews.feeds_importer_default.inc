<?php
/**
 * @file
 * directnews.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function directnews_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'directnews';
  $feeds_importer->config = array(
    'name' => 'Directnews',
    'description' => 'Import feeds from directnews',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => 1,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'DirectnewsParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'feed_item',
        'expire' => '-1',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'heading',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'contents',
            'target' => 'field_feed_item_description',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'full_html',
      ),
    ),
    'content_type' => 'directnewsfeed',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['directnews'] = $feeds_importer;

  return $export;
}
