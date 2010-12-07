<?php

if (!session::checkAccessControl('allow_system_backup_create')){
    return;
}

include_once _COS_PATH . "/scripts/common.php";
include_once _COS_PATH . "/scripts/commands/db.php";

systemBackup::listDbDumps();