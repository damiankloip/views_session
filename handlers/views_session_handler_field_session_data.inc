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
  function render($values) {
    $value = $this->get_value($values);
    if (!empty($value)) {
      $session_data = $this->session_unserialize($value);
      return var_export($session_data, TRUE);
    }
  }

  function session_unserialize($value) {
    $result = array();

    // prefixing with semicolon to make it easier to write the regular expression.
    $value = ';' . $value;

    $keyreg = '/;([^|{}"]+)\|/';

    // find all keys.
    $matches = array();
    preg_match_all($keyreg, $value, $matches);

    // only go further if we found some keys.
    if (isset($matches[1])) {
      $keys = $matches[1];

      // find the values by splitting the input on the key regular expression.
      $values = preg_split($keyreg, $value);

      // unshift the first value since it's always empty (due to our semicolon prefix).
      if (count($values) > 1) {
        array_shift($values);
      }

      // combine the $keys and $values.
      $result = array_combine($keys, $values);
    }

    return $result;
  }

}
