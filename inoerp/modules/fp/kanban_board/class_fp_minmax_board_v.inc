<?php

class fp_minmax_board_v extends dbObject {

 public static $table_name = "fp_minmax_board_v";
 public static $primary_column = "onhand_id";
 public $field_a = [
  'onhand_id',
  'item_number',
  'item_description',
  'org_name',
  'subinventory',
  'locator',
  'uom_id',
  'onhand',
  'minmax_min_quantity',
  'minmax_max_quantity',
  'item_id_m',
  'revision_name',
  'org_id',
  'subinventory_id',
  'locator_id',
  'lot_id',
  'serial_id',
  'reservable_onhand',
  'transactable_onhand',
  'lot_status',
  'serial_status',
  'secondary_uom_id',
  'onhand_status',
  'ef_id',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
 public $initial_search = [
  'onhand_id',
  'item_number',
  'item_description',
  'org_name',
  'subinventory',
  'locator',
  'uom_id',
  'onhand',
  'item_id_m',
  'org_id',
  'subinventory_id',
  'locator_id',
 ];
 public $dateField = [
 ];
 public $pageTitle = " Onhand - Find Inventory Onhand "; //page Title
 public $search = [
  '_view_path' => 'form.php?class_name=inv_onhand_serial',
  '_show_view_path' => 1,
  '_view_action_meassge' => 'Serial Numbers',
  '_extra_path' => array('form.php?class_name=inv_lot_onhand&mode=2' => 'Lot Numbers')
 ];
 public $search_groupBy = [
  'item_number' => 'Item Number'
//		 'locator' => 'Locator',
//		 'subinventory' => 'Sub Inventory',
//		 'org_id' => 'Inventory Org',
 ];
 public $search_groupBy_sum = 'onhand';
 public $ra_onhand_by_subinventoryType_parameters = [
  'Result Limit' => 'ra_result_limit',
  'Chart Type' => 'ra_chart_type',
 ];
 public $ra_onhand_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand Quantity By Subinventory Type',
  '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand Value By Subinventory Type',
  '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_settings = [
  '_chart_name' => 'Onhand Quantity By Product Line',
  '_x_axis_text' => 'Onhand Quantity',
 ];
 public $ra_onhand_value_by_productLine_settings = [
  '_chart_name' => 'Onhand Value By Product Line',
  '_x_axis_text' => 'Onhand Value',
 ];
 public $ra_onhand_by_productLine_subinventoryType_settings = [
  '_chart_name' => 'Onhand By Product Line Subinventory Type',
  '_chart_width' => '750',
  '_chart_height' => '450',
  '_x_axis_text' => 'Onhand Quantity',
  '_chart_type' => 'clustered_column',
  '_gap_between_xaxis_text' => '50',
  '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType_settings = [
  '_chart_name' => 'Onhand By Subinventory Type',
  '_chart_width' => '350',
  '_chart_height' => '350',
  '_x_axis_text' => 'Sub Invnetory Type',
  '_chart_type' => array('horizonatl_bar', 'vertical_column', 'pie'),
  '_legend' => ''
 ];
 public $ra_report_set_onhand_by_subinventoryType = [
  'ra_onhand_by_subinventoryType',
  'ra_onhand_value_by_subinventoryType',
  'ra_onhand_by_productLine',
  'ra_onhand_value_by_productLine',
  'ra_onhand_by_productLine_subinventoryType'
 ];
 public $onhand_id;
 public $item_number;
 public $item_description;
 public $product_line;
 public $org_name;
 public $subinventory;
 public $subinventory_type;
 public $locator;
 public $uom_id;
 public $onhand;
 public $minmax_min_quantity;
 public $minmax_max_quantity;
 public $open_po;
 public $item_id_m;
 public $revision_name;
 public $org_id;
 public $subinventory_id;
 public $locator_id;
 public $lot_id;
 public $serial_id;
 public $reservable_onhand;
 public $transactable_onhand;
 public $lot_status;
 public $serial_status;
 public $secondary_uom_id;
 public $onhand_status;
 public $ef_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $planner;
 public $make_buy;
 public $fix_lot_multiplier;
 public $flm;
 public $total_delta;

 private function create_fp_minmax_board_v() {
  $sql = "
	 CREATE OR REPLACE VIEW minmax_board_v
(onhand_id, item_number, item_description, product_line, org_name, subinventory, locator,
uom_id,onhand, minmax_min_quantity, minmax_max_quantity, open_quantity,
standard_cost, onhand_value,
item_id_m, revision_name, org_id, subinventory_id, subinventory_type,
locator_id, lot_id, serial_id, reservable_onhand, 
transactable_onhand, lot_status, serial_status,  
secondary_uom_id, onhand_status, ef_id, created_by, 
creation_date, last_update_by, last_update_date, min_delta)
AS
SELECT onhand.onhand_id, 
item.item_number, item.item_description, item.product_line,
org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand, item.minmax_min_quantity, item.minmax_max_quantity, po_summary.open_quantity,
cic.standard_cost, (onhand.onhand * cic.standard_cost) as onhand_value,
onhand.item_id_m, onhand.revision_name, onhand.org_id, onhand.subinventory_id, subinventory.type,
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date,
(onhand.onhand + po_summary.open_quantity - item.minmax_min_quantity)as min_delta
FROM onhand  
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
LEFT JOIN 
 ( 
 SELECT SUM(open_quantity) as open_quantity, receving_org_id, item_id_m
 FROM po_all_v pav 
  WHERE receving_org_id IS NOT NULL
 AND open_quantity > 0
 GROUP BY  item_id_m, receving_org_id
 ) po_summary 
ON onhand.item_id_m = po_summary.item_id_m AND po_summary.receving_org_id = onhand.org_id 
LEFT JOIN cst_item_cost_v cic ON cic.item_id_m = onhand.item_id_m AND cic.bom_cost_type='FROZEN'
AND cic.org_id = onhand.org_id,
item

WHERE onhand.item_id_m = item.item_id_m 
AND item.org_id = onhand.org_id
AND item.minmax_min_quantity IS NOT NULL
";
 }

 public function findBy_itemIdm_location() {
  $sql = "SELECT * FROM " . self::$table_name;
  $sql .= " WHERE item_id_m = '{$this->item_id_m}' ";
  if (!empty($this->org_id)) {
   $sql .= " AND org_id = '{$this->org_id}' ";
  }
  if (!empty($this->subinventory_id)) {
   $sql .= " AND subinventory_id = '{$this->subinventory_id}' ";
  }
  if (!empty($this->locator_id)) {
   $sql .= " AND locator_id = '{$this->locator_id}' ";
  }

  $result = $this->findBySql($sql);
  return !empty($result) ? $result : false;
 }

 public static function find_by_itemId_orgId($item_id, $org_id) {
  $sql = " SELECT * from onhand_v WHERE item_id_m = '{$item_id}' "
   . " AND org_id = '{$org_id}' ";
  $result = self::find_by_sql($sql);
  return !empty($result) ? $result : false;
 }

 public static function find_by_orgId($org_id) {
  $sql = " SELECT * from onhand_v WHERE "
   . " AND org_id = '{$org_id}' ";
  $result = self::find_by_sql($sql);
  return !empty($result) ? $result : false;
 }

 public static function find_by_orgId_subInventoryId($org_id, $subinventory_id = '') {
  if (empty($org_id)) {
   return false;
  }

  $sql = " SELECT onhand.onhand_id, 
item.item_number, item.item_description, item.product_line,
org.org, subinventory.subinventory, locator.locator,
onhand.uom_id,onhand.onhand, item.minmax_min_quantity, item.minmax_max_quantity, 
(IFNULL(onhand.onhand,0) - IFNULL(item.minmax_min_quantity,0)) as onhand_delta, po_summary.open_quantity as open_po,
cic.standard_cost, (onhand.onhand * cic.standard_cost) as onhand_value,
onhand.item_id_m, onhand.revision_name, onhand.org_id, onhand.subinventory_id, subinventory.type,
onhand.locator_id, onhand.lot_id, onhand.serial_id, onhand.reservable_onhand, 
onhand.transactable_onhand, onhand.lot_status, onhand.serial_status,  
onhand.secondary_uom_id, onhand.onhand_status, onhand.ef_id, onhand.created_by, 
onhand.creation_date, onhand.last_update_by, onhand.last_update_date,
(IFNULL(onhand.onhand,0) + IFNULL(po_summary.open_quantity,0)- IFNULL(item.minmax_min_quantity,0))as total_delta,
item.fix_lot_multiplier as flm, item.planner, item.make_buy

FROM onhand  
LEFT JOIN org ON onhand.org_id = org.org_id
LEFT JOIN subinventory ON onhand.subinventory_id = subinventory.subinventory_id
LEFT JOIN locator ON onhand.locator_id = locator.locator_id
LEFT JOIN 
 ( 
 SELECT SUM(open_quantity) as open_quantity, receving_org_id, item_id_m
 FROM po_all_v pav 
  WHERE receving_org_id IS NOT NULL
 AND open_quantity > 0
 GROUP BY  item_id_m, receving_org_id
 ) po_summary 
ON onhand.item_id_m = po_summary.item_id_m AND po_summary.receving_org_id = onhand.org_id 
LEFT JOIN cst_item_cost_v cic ON cic.item_id_m = onhand.item_id_m AND cic.bom_cost_type='FROZEN'
AND cic.org_id = onhand.org_id,
item

WHERE onhand.item_id_m = item.item_id_m 
AND item.org_id = onhand.org_id
AND item.minmax_min_quantity IS NOT NULL 
AND onhand.org_id = '{$org_id}'";
  if (!empty($subinventory_id)) {
   $sql .= " AND onhand.subinventory_id = '{$subinventory_id}' ";
  }
  $sql .="  ORDER BY total_delta ASC ";

  $result = self::find_by_sql($sql);

  return !empty($result) ? $result : false;
 }



}

//end of po_detail class
?>