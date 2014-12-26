#include "otools.h"
#include "ui_otools.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QtGui>
#include <stdlib.h>
char* device("unknown");

OTools::OTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OTools)
{
    ui->setupUi(this);
}

OTools::~OTools()
{
    delete ui;
}

void done(){
}

// Device Selection

void OTools::on_bacon_clicked()
{
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->UnlockB->setEnabled(true);
    ui->LockB->setEnabled(true);
    ui->EfsB->setEnabled(true);
    ui->label->setVisible(false);
    device="bacon";
    setenv("adbdevice", device, true);
}

void OTools::on_find7_clicked(){
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    device="find7";
    setenv("adbdevice", device, true);
}

void OTools::on_find5_clicked()
{
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    device="find5";
    setenv("adbdevice", device, true);
}

void OTools::on_n1_clicked()
{
    ui->modbox->setEnabled(true);
    ui->recbox->setEnabled(true);
    ui->filebox->setEnabled(true);
    ui->backbox->setEnabled(true);
    ui->label->setVisible(false);
    ui->UnlockB->setEnabled(false);
    ui->LockB->setEnabled(false);
    ui->EfsB->setEnabled(false);
    device="n1";
    setenv("adbdevice", device, true);
}

// ToolBar

void OTools::on_actionDisclaimer_triggered()
{
    QMessageBox::critical(this,tr("Disclaimer"),"This program has enough knowledge to brick your device, destroy your computer, void warrany, eat cats and burn your flowers. The developer disclaim every damange caused from the usage of this program.", "Close");
}

void OTools::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("About OTools"),"©2014 Joey Rizzoli (@linuxx)\nSources: https://github.com/linuxxxxx/OTools\nOTools is an opensource software that has the goal to provide a fast, safe and user friendly tool to manage your Oppo or OnePlus Device.");
}

void OTools::on_actionUpdate_triggered()
{
    QMessageBox::information(this,tr("Update"),"Click Start to update OTools");
}

// Buttons

/* TODO:
 * Dialog while executing system()
 * Check if system() returned 0
 */


//Backup

void OTools::on_BackupB_clicked()
{
    QString backfile=QFileDialog::getSaveFileName(this, tr("Save file"), "", ".ab");
    QMessageBox::information(this,tr("Backup"),backfile,"OK");
    const char *backupf = qPrintable(backfile);
    setenv("backupf", backupf, true);
    system("adb backup -apk -nosystem -noshared f $backupf");
    QMessageBox::information(this,tr("Backup"),"Done!","OK");
    /* TODO:
     * figure out why the file is not saved, the var is ok
     */
}

void OTools::on_RestoreB_clicked()
{
    QString backfile=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "Backups (*.ab);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Restore Backup"),backfile,"OK");
    const char *backupf = qPrintable(backfile);
    setenv("backupf", backupf, true);
    system("adb restore $backupf");
    QMessageBox::information(this,tr("Restore Backup"),"Done!","OK");
}

//Files

void OTools::on_PushB_clicked(){
    QString pushfile=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "All Files (*.*)"
                );
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Push File", pushfile,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      const char *file = qPrintable(pushfile);
      setenv("pushfile", file, true);
      system("adb push $pushfile /sdcard/");
      QMessageBox::information(this,tr("Push File"),"Done!","OK");
    }
}

void OTools::on_PullB_clicked(){
    /* TODO:
     * dunno
     */
}

void OTools::on_CamB_clicked(){
    /* TODO:
     * something similar to pull, but instead of selecting a file, make user select the destination folder for the photos
     * On aosp roms the dcim path is /sdcard/DCIM/Camera
     */
}

//Recovery

void OTools::on_pushButton_3_clicked()
{
    /* TODO:
     * if install zip is cheked enable the select button, export the path as bash var, add the flag to openrecovery script
     * if wipe data is checked add a flag to openrecovery script
     * if backup is checked add a flag to openrecovery script
     */
}

// Advanced stuffs

//MOD

void OTools::on_UnlockB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Unlock Bootloader", "You want to unlock the bootloader,\nthis operation will erase all your personal content such as photos, apps and music, a backup is recommend!\nThis operation may brick your device if something goes wrong.\nAre you sure you want to unlock your device?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      system("adb wait-for-device");
      system("adb reboot bootloader");
      system("fastboot devices");
      system("fastboot oem-unlock");
      // Dunno how that lk manages fb commands,
      QMessageBox::information(this,tr("Unlock Bootloader"),"Wait until the device completes the operation.","Done");
    }
}

void OTools::on_LockB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Lock Bootloader", "You want to lock the bootloader, you won't be able to boot or flash img files until you'll re-unlock it! You won't loose any data.\n This operation may brick your device if something goes wrong.\nAre you sure you want to unlock your device?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      system("adb wait-for-device");
      system("adb reboot bootloader");
      system("fastboot devices");
      system("fastboot oem-lock");
      QMessageBox::information(this,tr("Lock Bootloader"),"Done!","OK");
    }
}

void OTools::on_FBootB_clicked()
{
    QString fbboot=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "IMG files (*.img);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Fastboot Boot"),fbboot,"OK");
    const char *ffbboot = qPrintable(fbboot);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Fastboot Boot", "Do you want to sideload/boot an img file from your computer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        setenv("ffbboot", ffbboot, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot devices");
        system("fastboot boot $ffbboot");
        QMessageBox::information(this,tr("Fastboot Boot"),"Done!","OK");
    }
}

void OTools::on_FlashBootB_clicked()
{
    QString fboot=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "IMG files (*.img);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Kernel Installer"),fboot,"OK");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Kernel Installer", "Do you want to install a new kernel from img?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *ffboot = qPrintable(fboot);
        setenv("ffboot", ffboot, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot devices");
        system("fastboot flash boot $ffboot");
        system("fastboot reboot");
        QMessageBox::information(this,tr("Kernel Installer"),"Done!","OK");
    }
}

void OTools::on_RecoveryB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Recovery Installer", "Do you already have a recovery for your device on the pc?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString recovery=QFileDialog::getOpenFileName(
                    this,
                    tr("Choose File"),
                    "~"
                    "IMG files (*.img);;All Files (*.*)"
                    );
        QMessageBox::information(this,tr("Recovery Installer"),recovery,"OK");
        const char *frecovery = qPrintable(recovery);
        setenv("frecovery", frecovery, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot devices");
        system("fastboot flash recovery $frecovery");
        system("fastboot reboot");
        QMessageBox::information(this,tr("Recovery Installer"),"Done!","OK");
    } else {
        char* recovery("res/$adbdevice/recovery.img");
        setenv("frecovery", recovery, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot devices");
        system("fastboot flash recovery $ffboot");
        system("fastboot reboot");
        QMessageBox::information(this,tr("Recovery Installer"),"Done!","OK");
    }
}

void OTools::on_FBFlashB_clicked()
{
    /* TODO >>LATER<<:
     * ask partition name (choose from an array?)
     * Filepicker
     * flash
     */
}

void OTools::on_RootB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Rooter", "This operation will root your device.\nBootloader must be unlocked otherwhise it fail.\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //TODO: add a unlocked-checker using fastboot oem device-info | grep 'Device unlocked: '
        const char *updatezip("res/root.zip");
        setenv("updatezip", updatezip, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot device");
        system("fastboot boot res/$adbdevice/recovery.img");
        // TODO: find a better way to inject openrecovery commands
        system("sh res/openrecovery.sh --sideload");
        QMessageBox::information(this,tr("Rooter"),"Done!","OK");
    }
}

void OTools::on_LogoB_clicked()
{
    QString logo=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "Logo files (*.bin);;All Files (*.*)"
                );
    QMessageBox::information(this,tr("Logo Changer"),logo,"OK");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Logo Changer", "This operation will change your bootlogo (Your bootloader needs to be unlocked otherwhise it will fail).\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        const char *flogo = qPrintable(logo);
        setenv("flogo", flogo, true);
        system("adb wait-for-device");
        system("adb reboot bootloader");
        system("fastboot devices");
        system("fastboot flash LOGO $flogo");
        system("fastboot reboot");
        QMessageBox::information(this,tr("Logo Changer"),"Done!","OK");
    }
}

void OTools::on_EfsB_clicked()
{
    QMessageBox::information(this,tr("EFS Backup"),"You need root access in order to backup efs","Continue");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "EFS Backup", "This operation will backup efs on the top of your sdcard.\nYou need root access otherwhise it will fail\nDo you want to continue?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      system("adb wait-for-device");
      system("adb shell 'dd if=/dev/block/mmcblk0p10 of=/sdcard/modemst1.bin bs=512'");
      system("adb shell 'dd if=/dev/block/mmcblk0p11 of=/sdcard/modemst2.bin bs=512'");
          QMessageBox::information(this,tr("EFS Backup"),"Done!","OK");
    }
}

void OTools::on_SRECB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Screen Recorder", "You need android 4.4.x+ in order to record your screen.\nUnPlug the device when you want to stop the registration.\nThe program will freeze until it's working.\n Do you want to start?)",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QMessageBox::information(this,tr("Screen Recorder"), "UnPlug the device when you want to stop the registration.\nAll the other features will be disabled!");
        //freeze the program and update the suggestion text
        ui->backbox->setEnabled(false);
        ui->modbox->setEnabled(false);
        ui->recbox->setEnabled(false);
        ui->filebox->setEnabled(false);
        system("adb shell screenrecord /sdcard/video.mp4");
        ui->modbox->setEnabled(true);
        ui->recbox->setEnabled(true);
        ui->filebox->setEnabled(true);
        ui->backbox->setEnabled(true);
        QMessageBox::information(this,tr("Screen Recorder"),"Done!","OK");
    }
}

void OTools::on_ShellB_clicked()
{
    /* TODO:
     * open xterm with adb shell << I don't like this
     */
}

void OTools::on_ApkB_clicked()
{
    QString apk=QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "~"
                "Apk files (*.apk);;All Files (*.*)"
                );
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Apk Installer",apk ,
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        const char *fapk = qPrintable(apk);
        setenv("fapk", fapk, true);
        system("adb wait-for-device");
        system("adb install $fapk");
        QMessageBox::information(this,tr("Apk Installer"),"Done!","OK");
      QApplication::quit();
    }
}
