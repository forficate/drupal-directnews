<?php
class DirectnewsParser extends FeedsParser {

 /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    
    if (!defined('LIBXML_VERSION') || (version_compare(phpversion(), '5.1.0', '<'))) {
      @ $xml = simplexml_load_string($fetcher_result->getRaw(), NULL);
    }
    else {
      @ $xml = simplexml_load_string($fetcher_result->getRaw(), NULL, LIBXML_NOERROR | LIBXML_NOWARNING | LIBXML_NOCDATA);
    }
  
    // Got a malformed XML.
    if ($xml === FALSE || is_null($xml)) {
      return FALSE;
    }
    
    $items=array();
    
    foreach($xml->Article as $article){
    	$items[] = $this->parseArticleElement($article);    	
    }
       
    
    return new FeedsParserResult($items);
  }

  /**
   * Return mapping sources.
   *
   */
  public function getMappingSources() {
    return array(
      'heading' => array(
        'name' => t('Heading'),
        'description' => t('Title of the feed item.'),
      ),
      'created' => array(
        'name' => t('Created'),
        'description' => t('Published date as UNIX time GMT of the feed item.'),
      ),
      'contents' => array(
        'name' => t('Contents'),
        'description' => t('The article.'),
      ),
      'summary' => array(
        'name' => t('Summary'),
        'description' => t('Article summary.'),
      ),
      'guid' => array(
        'name' => t('Item ID'),
        'description' => t('Unique Identifier of the feed item.'),
      ),
     ) + parent::getMappingSources();
  }
  
  private function parseArticleElement($articleElement){
  	
  	$createdTime = "{$articleElement->attributes()->Created}";
  	$createdDate = "{$articleElement->Date}";
  	list($day, $month, $year) = split('[/]', $date);
  	$created = strtotime($year . "-" . $month . "-" . $day . " " . $createdTime);
  	
  	
  	return array(
    		'heading' => "{$articleElement->Heading}",
    		'created' => $created,
    		'contents' => "{$articleElement->Contents}",
    		'summary' => "{$articleElement->Summary}",
    		'guid' => "{$articleElement->attributes()->ID}" //Unique identidier to manage updates / duplicates
    );
  }


}
