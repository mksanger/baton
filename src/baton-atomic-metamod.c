/**
 * Copyright (C) 2021 Genome Research
 * Ltd. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Michael Kubiak <mk35@sanger.ac.uk>
 */

#include "baton.h"

#include <atomic_apply_metadata_operations.h> //not available through apiHeaderAll.h

/*
  Current Error: remote addresses: 127.0.0.1 ERROR: procApiRequest: apiTableLookup of apiNumber 20002 failed
*/
int main() {
    rodsEnv env;
    rcComm_t *conn = rods_login(&env);
    /* size_t jflags = JSON_DISABLE_EOF_CHECK | JSON_REJECT_DUPLICATES;
    FILE *in = maybe_stdin(NULL);
    json_error_t load_error;
    json_t *json_in = json_loadf(in, jflags, &load_error);
    if (!json_in) {
        printf("Load error: %s\n", load_error.text);
        return (1);
    } else if (!json_is_object(json_in)) {
        printf("not an object\n");
        return (2);
    } */

    /* 
       baked in json string for simplicity, but it also fails when passing: 
       jq -n '{entity_name: "test.txt", entity_type: "data_object", operations: [{operation: "add", attribute: "attr", value: "val"}]}' | baton-atomic-metamod
       with the above stdin parsing
    */
    char *json_str =
        "{\"entity_name\": \"compile_commands.json\", \"entity_type\": "
        "\"data_object\", \"operations\": \"[{\\\"operation\\\": \\\"add\\\", "
        "\\\"attribute\\\": \\\"attr\\\", \\\"value\\\": \\\"val\\\"}]\"}";

    char *results;
    /* char *json_str = json_dumps(json_in, jflags); */
    printf("json_str: %s\n", json_str);
    int irods_error = rc_atomic_apply_metadata_operations(
                               conn, json_str, &results);
    printf("irods error: %d\n", irods_error);
    printf("Result: %s\n", results);
    return (0);
}
