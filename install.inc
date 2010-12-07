<?php

$_INSTALL['VERSION'] = 1.01;

$_INSTALL['SUB_MENU_ITEM'] = array (
    'title' => 'system_backup', // Title of the menu item
    'url' => '/system_backup/list', // url of the item
    'module_name' => 'system_backup', // beloning to which module
    // note that we set the parent module
    'parent' => 'system',
    'auth' => 'admin'

);

$_INSTALL['PARENT'] = 'system';

$_INSTALL['PUBLIC_CLONE_URL'] = 'git://github.com/diversen/system_backup.git';