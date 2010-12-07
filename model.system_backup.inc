<?php



include_once _COS_PATH . "/scripts/shell_base/common.inc";
include_once _COS_PATH . "/scripts/shell_base/db.inc";

// {{{ dump_db()
/**
 * function for dumping a database specfied in config.ini to a file
 *
 * (modified from script/db/dump_db_file)
 *
 * @param   array   Optional. If you leave empty, then the function will try
 *                  and find most recent sql dump and load it into database.
 *                  Set <code>$options = array('File' => '/backup/sql/latest.sql')</code>
 *                  for setting a name for the dump.
 * @return  int     the executed commands shell status 0 on success.
 */

class systemBackup {

    public static $backupDir = "/htdocs/files/system_backup";
    public static $max = 3;

    public static function createBackupDir (){
        $system_backup_dir = _COS_PATH . self::$backupDir;
        if (!file_exists($system_backup_dir)){
            echo lang::translate('system_backup_dir_not_exists') . "<br />";
            $ret = mkdir($system_backup_dir);
            if ($ret){
                echo lang::translate('system_backup_dir_created') . "<br />";
            } else {
                echo lang::translate('system_backup_dir_could_not_be_created') . "<br />";
            }
        }
    }

    public static function dumpDbFile (){

        $dump_name = _COS_PATH . self::$backupDir . "/" . time() . ".sql";

        $db = get_db_info();
        $command =
            "mysqldump --opt -u" . register::$vars['coscms_main']['username'] .
            " -p" . register::$vars['coscms_main']['password'];
        $command.= " $db[name] > $dump_name";
        return (cos_exec($command));
    }

    public static function listDbDumps (){

        $system_backup_dir = _COS_PATH . self::$backupDir;
        $max = self::$max;

        if (!file_exists($system_backup_dir)){
            return;
        }

        $latest = scandir($system_backup_dir);
        $latest = array_reverse($latest);

        foreach ($latest as $key => $val){
            if ($val == '.' || $val == '..'){
                unset($latest[$key]);
                continue;
            }
        }

        $str = '';
        
        foreach ($latest as $key => $val){
            $file = $val;
            $file = explode('.', $val);
            if (is_numeric($file[0])){
                  $str.= date("Y-m-d G:i:s", $file[0]);
                  $str.= " " . self::viewAdminOptions($val) . "<br />";

            }
        }
        if ($str != ''){
            $str = lang::translate('system_backup_timestamp_format') ."<br />" . $str; 
        }
        print $str;
    }

    public static function viewAdminOptions ($file){
        $str = create_link("/system_backup/regenerate/$file", lang::translate('system_backup_regenerate'));
        $str.= " | ";
        $str.= create_link("/system_backup/delete/$file", lang::translate('system_backup_delete'));
        return $str;

    }

    public static function delete ($file){
        $delete_file = _COS_PATH . self::$backupDir . "/$file";
        $res = unlink($delete_file);
       
        return $res;
    }

    public static function regenerate ($file){
        $regenerate_file = _COS_PATH . self::$backupDir . "/$file";
        $options = array ();
        $options['File'] = $regenerate_file;
        $res = load_db_file($options);
        return $res;
    }

    public static function countBackupFiles (){
        $system_backup_dir = _COS_PATH . self::$backupDir;

        $latest = scandir($system_backup_dir);
        $latest = array_reverse($latest);

        foreach ($latest as $key => $val){
            if ($val == '.' || $val == '..'){
                unset($latest[$key]);
                continue;
            }
        }

        return count($latest);
    }
}
