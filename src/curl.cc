#include <stdio.h>
#include <curl/curl.h>

namespace sr_curl
{
// const char *post(const char *url, const char *data)
// {
//   CURL *curl;
//   CURLcode res;

//   // curl_global_init(CURL_GLOBAL_ALL);
//   curl = curl_easy_init();

//   if (curl)
//   {
//     curl_easy_setopt(curl, CURLOPT_URL, url);
//     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

//     res = curl_easy_perform(curl);
//     if (res != CURLE_OK)
//     {
//       char *msg;
//       sprintf(msg, "%s", curl_easy_strerror(res));
//       return msg;
//     }

//     curl_easy_cleanup(curl);
//   }
//   // curl_global_cleanup();
//   return "ok";
// }

const char *upload(const char *url, const char *filePath)
{
  CURL *curl;
  CURLcode res;
  char *errMsg = NULL;

  curl = curl_easy_init();
  if (!curl)
    return "无法构建curl对象";
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(curl, CURLOPT_PUT, 1L);

  FILE *fp = fopen(filePath, "rb");
  if (!fp)
  {
    sprintf(errMsg, "文件无法打开文件：%s", filePath);
    return errMsg;
  }
  fseek(fp, 0, SEEK_END); // 将文件指针移动文件结尾
  long fsize = ftell(fp);

  curl_easy_setopt(curl, CURLOPT_READDATA, fp);
  curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, fsize);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(curl);

  fclose(fp);
  if (res != CURLE_OK)
  {
    sprintf(errMsg, "%s", curl_easy_strerror(res));
    return errMsg;
  }

  return "ok";
}
} 