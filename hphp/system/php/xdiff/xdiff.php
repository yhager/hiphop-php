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

function xdiff_file_bdiff_size(string $file) : int {
  return xdiff_string_bdiff_size(file_get_contents($file));
}

function xdiff_file_bdiff(string $old_file, string $new_file, string $dest) : bool {
  $bdiff = xdiff_string_bdiff(file_get_contents($old_file),
                              file_get_contents($new_file));
  if ($bdiff === FALSE)
    return FALSE;

  $ret = file_put_contents($dest, $bdiff);
  return $ret >= 0;
}

function xdiff_file_bpatch(string $file, string $patch, string $dest) : bool {
  $patched = xdiff_string_bpatch(file_get_contents($file), $patch);
  if ($patched === FALSE)
    return FALSE;

  $ret = file_put_contents($dest, $patched);
  return $ret >= 0;
}

function xdiff_file_diff_binary(string $old_file, string $new_file, string $dest):bool {
  return xdiff_file_bdiff($old_file, $new_file, $dest);
}

function xdiff_file_diff(string $old_file, string $new_file, string $dest, int $context /* = 3 */, bool $minimal /* = FALSE */) : bool {
  $diff = xdiff_string_diff(file_get_contents($old_file),
                            file_get_contents($new_file),
                            $context, $minimal);

  if ($diff === FALSE)
    return FALSE;

  $ret = put_file_contents($dest, $diff);

  return $ret >= 0;
}

function xdiff_file_merge3(string $old_file, string $new_file1, string $new_file2, string $dest) : mixed {
  $merged = xdiff_string_merge3(file_get_contents($old_file),
                                file_get_contents($new_file1),
                                file_get_contents($new_file2),
                                $error);
  if ($merged === FALSE)
    return FALSE;

  $ret = put_file_contents($dest, $merged);

  if (!empty($error))
    return $error;

  return $ret >= 0;
}

function xdiff_file_patch_binary(string $file, string $patch, string $dest): bool {
  return xdiff_file_bpatch($file, $patch, $dest);
}

function xdiff_file_patch(string $file, string $patch, string $dest,
                          int $flags /* = DIFF_PATCH_NORMAL */): mixed {
  $patched = xdiff_string_patch(file_get_contents($file), $patch, $flags, $error);

  if ($patched === FALSE)
    return FALSE;

  $ret = put_file_contents($dest, $patched);

  if (!empty($error))
    return $error;

  return ($ret>=0);
}

function xdiff_file_rabdiff(string $old_file, string $new_file, string $dest): bool {
  $rabdiff = xdiff_string_rabdiff(file_get_contents($old_file),
                                  file_get_contents($new_file));
  if ($rabdiff) {
    $ret = file_put_contents($dest, $rabdiff);
  }

  return ($ret>=0);
}