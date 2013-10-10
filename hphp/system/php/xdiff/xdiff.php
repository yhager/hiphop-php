<?php

/**
 * xdiff_string_rabdiff() - http://php.net/function.xdiff_string_rabdiff
 *
 * @param string $old_data - First string with binary data. It acts as "old" data.
 * @param string $new_data - Second string with binary data. It acts as "new" data
 *
 * @return string - binary diff containing differences between "old" and "new"
 *                  data or FALSE if an internal error occurred
 */
<<__Native>>
function xdiff_string_rabdiff(string $old_data, string $new_data): mixed;

function xdiff_php_test(): bool {
  echo "Hello from xdiff_php\n";
  return true;
}