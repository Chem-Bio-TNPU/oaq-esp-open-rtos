/*
 * Configuration parameters.
 *
 * Licensed under the Apache License, Version 2.0, January 2004 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 *
 */

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "sysparam.h"

/*
 * Parameters.
 *
 * If not sufficiently initialized to communicate with a server then
 * wifi is disabled and the post-data task is not created.
 *
 * The 'board' can be 0 for Nodemcu, and 1 for Witty.
 */
char *param_web_server;
char *param_web_port;
char *param_web_path;
uint32_t param_sensor_id;
uint32_t param_key_size;
uint8_t *param_sha3_key;
uint8_t param_board;
uint8_t param_pms5003_serial;
char *param_wifi_ssid;
char *param_wifi_pass;

void init_params()
{
    sysparam_status_t status;

    param_board = 0;
    param_pms5003_serial = 0;
    param_wifi_ssid = NULL;
    param_wifi_pass = NULL;
    param_web_server = NULL;
    param_web_port = NULL;
    param_web_path = NULL;
    param_sensor_id = 0;
    param_key_size = 0;
    param_sha3_key = NULL;

    sysparam_get_int8("board", (int8_t *)&param_board);
    sysparam_get_int8("pms5003_serial", (int8_t *)&param_pms5003_serial);
    sysparam_get_string("wifissid", &param_wifi_ssid);
    sysparam_get_string("wifipass", &param_wifi_pass);
    
    sysparam_get_string("web_server", &param_web_server);
    sysparam_get_string("web_port", &param_web_port);
    sysparam_get_string("web_path", &param_web_path);

    sysparam_get_int32("sensor_id", (int32_t *)&param_sensor_id);
    sysparam_get_int32("key_size", (int32_t *)&param_key_size);
    size_t actual_length;
    status = sysparam_get_data("key", &param_sha3_key, &actual_length, NULL);
    if (status != SYSPARAM_OK || actual_length != param_key_size) {
        param_key_size = 0;
        param_sha3_key = NULL;
    }
}