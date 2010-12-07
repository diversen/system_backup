<?php

if (!session::checkAccessControl('allow_system_backup_create')){
    return;
}

if (isset($_POST['delete'])){
    $file = uri::$fragments[2];
    $res = systemBackup::delete($file);
    if ($res){
        session::setActionMessage(lang::translate('system_backup_file_deleted'));
    } else {
        session::setActionMessage(lang::translate('system_backup_file_deleted_failed'));
    }
    
    $header = "Location: /system_backup/list";
    header($header);
    die;
}


?>

<?=lang::translate('system_backup_delete')?>
<form method ="post" action="">
<input type="submit" name="delete" value ="<?=lang::translate('system_backup_delete_confirm')?>" />
</form>