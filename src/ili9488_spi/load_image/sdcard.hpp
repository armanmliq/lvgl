#include <SPI.h>
#include <SD.h>
#include <FS.h>

static void *sd_open_cb(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
  // File *fp = (File *)lv_mem_alloc(sizeof(File));

  File *fp = new (File); // when opening file

  if (fp == NULL)
    return NULL;

  File mySDfile = *fp;

  /*Make the path relative to the current directory (the projects root folder)*/
  char buf[256];
  sprintf(buf, "/%s", path);

  if (mode == LV_FS_MODE_WR)
  {
    /*Open a file for write*/
    mySDfile = SD.open(buf, FILE_WRITE);
  }
  else if (mode == LV_FS_MODE_RD)
  {
    /*Open a file for read*/
    mySDfile = SD.open(buf, FILE_READ);
  }
  else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
  {
    /*Open a file for read and write*/
    mySDfile = SD.open(buf, FILE_WRITE);
  }

  // make sure at the beginning
  mySDfile.seek(0);

  *fp = mySDfile;

  return fp;
}

/**
 * Close an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t sd_close_cb(lv_fs_drv_t *drv, void *file_p)
{
  File *fp = (File *)file_p; /*Just avoid the confusing casings*/

  fp->close();

  delete (fp); // when close
  return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param buf       pointer to a memory block where to store the read data
 * @param btr       number of Bytes To Read
 * @param br        the real number of read bytes (Byte Read)
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */

static lv_fs_res_t sd_read_cb(lv_fs_drv_t *drv, void *file_p, void *fileBuf, uint32_t btr, uint32_t *br)
{
  // Serial.println("Call Back Asked to read file");

  File *fp = (File *)file_p; /*Just avoid the confusing casings*/
  File fileSD = *fp;

  // Serial.println((int)fileSD.available());

  *br = fileSD.read((uint8_t *)fileBuf, btr);

  lv_fs_res_t res = LV_FS_RES_OK;
  return res;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable. (opened with fs_open )
 * @param pos       the new position of read write pointer
 * @param whence    tells from where to interpret the `pos`. See @lv_fs_whence_t
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t sd_seek_cb(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
  lv_fs_res_t res = LV_FS_RES_OK;

  // FsFile *fp = (FsFile *)file_p; /*Just avoid the confusing casings*/
  File *fp = (File *)file_p; /*Just avoid the confusing casings*/

  if (whence == LV_FS_SEEK_SET)
  {
    fp->seek(pos, SeekMode::SeekSet);
  }
  if (whence == LV_FS_SEEK_CUR)
  {
    fp->seek(pos, SeekMode::SeekCur);
  }
  if (whence == LV_FS_SEEK_END)
  {
    fp->seek(pos, SeekMode::SeekEnd);
  }
  return res;
}

/**
 * Give the position of the read write pointer
 * @param drv       pointer to a driver where this function belongs
 * @param file_p    pointer to a file_t variable.
 * @param pos_p     pointer to to store the result
 * @return          LV_FS_RES_OK: no error or  any error from @lv_fs_res_t enum
 */
static lv_fs_res_t sd_tell_cb(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
  // FsFile *fp = (FsFile *)file_p; /*Just avoid the confusing casings*/
  File *fp = (File *)file_p; /*Just avoid the confusing casings*/
  *pos_p = fp->position();

  return LV_FS_RES_OK;
}

static bool sd_ready_cb(struct _lv_fs_drv_t *drv)
{
  return 1;
}

void lvgl_fs_test(void)
{
    char rbuf[30] = {0};
    uint32_t rsize = 0;
    lv_fs_file_t fd;
    lv_fs_res_t res;

    res = lv_fs_open(&fd, "S:foo.txt", LV_FS_MODE_RD);
    if (res != LV_FS_RES_OK) {
    	ESP_LOGI(TAG,"open /123.txt ERROR\n");
        return ;
    }

    res = lv_fs_read(&fd, rbuf, 100, &rsize);
    if (res != LV_FS_RES_OK) {
    	ESP_LOGI(TAG,"read ERROR\n");
        return ;
    }

    ESP_LOGI(TAG,"READ(%d): %s",rsize , rbuf);
    lv_fs_close(&fd);
}