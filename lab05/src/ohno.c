/*********************************************

CIS330: Lab 3

Implementation file for the error reporting system

*********************************************/

#include <stdlib.h>
#include <string.h>
#include <ohno.h>

static struct ohno_state *state;

/*
 * Initialize the ohno error system with the given file stream and application name.
 *
 * This should allocate and populate the state structure.
 * Make sure to make a copy of `app_name` as we'll need to use this string later when `ohno()` is called.
 *
 * Feel free to return non-zero if anything went wrong (like not having sufficient memory).
 */
int
ohno_init(FILE* where_to, const char* app_name)
{
	// allocate state instance
	state = (struct ohno_state *) malloc(sizeof(struct ohno_state));
	if (!state) return 1;

	state->out = where_to;

	int str_len = strlen(app_name);
	
	// allocate memory for name
	state->name = (char *) malloc(sizeof(char) * (str_len + 1));
	if (!state->name) return 1;

	// copy app_name to state name
	for (int i = 0; i < str_len; i++) {
		state->name[i] = app_name[i];
	}
	state->name[str_len] = '\0';

	// init error number
	state->error_number = 0;

  return 0;
}

/*
 * Free any memory allocated to the ohno error system.
 *
 * You allocated memory in `ohno_init()`, now you must give it back.
 */
void
ohno_free()
{
	free(state->name);
	free(state);

}

/*
 * Report an error or warning given the current ohno error system settings (from ohno_init())
 *
 * This function should format `message` and `severity` along with the `app_name` string copied in `ohno_init()`
 * and write (print) a nice message on the saved `FILE *`.
 * The particular formating is up to you. Get creative if your like and feel free to add useful information
 * (e.g. error number or timestamp) to your report.
 */
void
ohno(const char* message, ohno_severity_t severity)
{
	// Print for each case
	switch (severity) {
		case OHNO_WARNING:
			fprintf(state->out, "WARNING %d: %s in %s\n", state->error_number, state->name, message);
			break;
		case OHNO_SERIOUS:
			fprintf(state->out, "SERIOUS %d: %s in %s\n", state->error_number, state->name, message);
			break;
		case OHNO_FATAL:
			fprintf(state->out, "FATAL %d: %s in %s\n", state->error_number, state->name, message);
			break;
	}
	
	// Increment error num
	state->error_number++;

}
