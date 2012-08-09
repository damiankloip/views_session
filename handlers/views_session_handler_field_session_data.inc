<?php

/**
 * @file
 * views_session_handler_field_session_data field handler.
 */

/**
 * Handler to display serialized session data.
 *
 * @ingroup views_field_handlers
 */
class views_session_handler_field_session_data extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['session_unserialize_format'] = array('default' => 'raw');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['session_unserialize_format'] = array(
      '#type' => 'select',
      '#title' => t('Session unserialized data format'),
      '#description' => t('The function/callback that will be used to display the unserliazed session data.'),
      '#options' => $this->unserialize_formats(),
      '#default_value' => $this->options['session_unserialize_format'],
    );

    parent::options_form($form, $form_state);
  }

  function render($values) {
    static $utility_inc = FALSE;
    $value = $this->get_value($values);

    if (!empty($value)) {
      if ($this->options['session_unserialize_format'] == 'raw') {
        return $value;
      }
      else {
        $session_data = $this->session_unserialize($value);
  
        if (!$utility_inc) {
          include DRUPAL_ROOT . '/includes/utility.inc';
          $utility_inc = TRUE;
        }
  
        return drupal_var_export($session_data);
      }
    }
  }

  /**
   * Unserialize session data, as session_decode() would do.
   */
  function session_unserialize($value) {
    $return = array();

    $parts = preg_split('/([a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff^|]*)\|/', $value, -1, PREG_SPLIT_NO_EMPTY | PREG_SPLIT_DELIM_CAPTURE);

    for($i = 0; $parts[$i]; $i += 2) {
      $return[$parts[$i]] = unserialize($parts[$i + 1]);
    }

    return $return;
  }

  /**
   * Return an array of formats to be used as form select options.
   */
  function unserialize_formats() {
    return array(
      'raw' => t('Raw'),
      'drupal_var_export' => t('Drupal var export'),
    );
  }

}
