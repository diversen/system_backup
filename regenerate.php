<?php

if (!session::checkAccessControl('allow_system_backup_create')){
    return;
}

ini_set('max_execution_time', 0);

if (isset($_POST['regenerate'])){
    $file = uri::$fragments[2];

    // note: return values is from exec command: 0 on success.
    $res = systemBackup::regenerate($file);
    if ($res == 0){
        session::setActionMessage(lang::translate('system_backup_file_regenerated'));
    } else {
        session::setActionMessage(lang::translate('system_backup_file_regenerated_failed'));
    }

    $header = "Location: /system_backup/list";
    header($header);
    die;
}

?>

<?=lang::translate('system_backup_regenerate')?>
<form method ="post" action="">
<input type="submit" name="regenerate" value ="<?=lang::translate('system_backup_regenerate_confirm')?>" />
</form>
