<?php

 class A {  public function __call($method, $args) {    for ($o = new MutableArrayIterator($args);         $o->valid(); $o->next()) {      $v = &$o->currentRef();      var_dump($v);      var_dump($v);    }    var_dump(array_key_exists('foo', $args));    var_dump(array_unshift($args, 4));    var_dump(array_pop($args));    if (isset($args['foo'])) {}    var_dump(each($args));    var_dump(array_shift($args));  }}$obj = new A;$obj->foo(1, 2, 3);