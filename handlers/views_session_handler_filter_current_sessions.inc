<?php

/**
 * @file
 * views_session_handler_filter_current_sessions filter handler.
 */

/**
 * Handler to filter whether a user has a current session.
 *
 * @ingroup views_filter_handlers
 */
class views_session_handler_filter_current_sessions extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'sessions', 'field' => 'uid');
  }

  function query() {
    $this->ensure_my_table();

    if ($this->value == 0) {
      $subselect = db_select('sessions', 's');
      $subselect->addField('s', 'sid');
      $subselect->where("s.uid = users.uid");

      $condition = db_or()->notExists($subselect);

      $this->query->add_where($this->options['group'], $condition);
    }
    else {
      parent::query();
    }
  }

}
