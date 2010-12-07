<?php

if (!session::checkAccessControl('allow_system_backup_create')){
    return;
}

include_module ('system_backup');

systemBackup::listDbDumps();