<?php

/**
 * @file
 * Views data hooks.
 */

/**
 * Implements hook_views_data().
 */
function views_session_views_data() {

  $data = array();

  $data['sessions']['table']['group'] = t('Session');

  $data['sessions']['table']['base'] = array(
    'field' => 'sid',
    'title' => t('Session'),
    'help' => t('Use data from the session table.'),
  );

  $data['sessions']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The sessions user ID'),
    'relationship' => array(
      'base' => 'users',
      'title' => t('User'),
      'help' => t('Relate a user to their session data.'),
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['uid_exists'] = array(
    'title' => t('User session status'),
    'help' => t('Whether the user has a current session or not.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['sid'] = array(
    'title' => t('Session ID'),
    'help' => t('The unique session ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['ssid'] = array(
    'title' => t('Secure session ID'),
    'help' => t('The Drupal secure session ID'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['hostname'] = array(
    'title' => t('Hostname'),
    'help' => t('The hostname for the session.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['timestamp'] = array(
    'title' => t('Time/date'),
    'help' => t('The time/date the session was started.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['timestamp_raw'] = array(
    'title' => t('Timestamp (raw)'),
    'help' => t('The time the session was started, In raw timestamp form.'),
    'real field' => 'timestamp',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['sessions']['cache'] = array(
    'title' => t('Cache'),
    'help' => t('The session cache status.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_boolean',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_boolean',
    ),
  );

  $data['sessions']['session'] = array(
    'title' => t('Session data'),
    'help' => t('The serialized session data.'),
    'field' => array(
      'handler' => 'views_session_handler_field_session_data',
      'click sortable' => TRUE,
    ),
  );

  // Specialised filter for user sessions.
  $data['sessions']['views_session_filter_current_users'] = array(
    'title' => t('Users with current sessions'),
    'help' => t('Filter for whether or not a user has a current session or not. This can be used to filter currently logged in users (or not).'),
    'real field' => 'uid',
    'filter' => array(
      'handler' => 'views_session_handler_filter_current_sessions',
      'type' => 'yes-no',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function views_session_views_data_alter(&$data) {
  // Add a relationship for the sessions user.
  $data['users']['views_session_user_rel'] = array(
    'group' => t('Session'),
    'title' => t('User session data'),
    'help' => t('Create a relationship between the user and their session data.'),
    'relationship' => array(
      'base' => 'sessions',
      'base field' => 'uid',
      'relationship field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User session data'),
    ),
  );
}
