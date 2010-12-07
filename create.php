<?php

if (!session::checkAccessControl('allow_system_backup_create')){
    return;
}

ini_set('max_execution_time', 0);

systemBackup::createBackupDir();


if (isset($_POST['backup'])){
    $ret = systemBackup::dumpDbFile();

    // note wehen we get return values from exec command
    // 0 is success anything else is failure
    if ($ret == 0){
        $message = lang::translate('system_backup_success');
        session::setActionMessage($message);

    } else {
        $message = lang::translate('system_backup_failure');
        session::setActionMessage($message);
    }

    $header = "Location: /system_backup/list";
    header($header);
    die;
}

$count_files = systemBackup::countBackupFiles();
if ($count_files >= systemBackup::$max){
    echo lang::translate('system_backup_limit_reached') . "<br>";
    return;
}


?>
<?=lang::translate('system_backup_info')?>
<form method ="post" action="">
<input type="submit" name="backup" value ="<?=lang::translate('system_backup_backup')?>" />
</form>