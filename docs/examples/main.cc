#include <pipewire/pipewire.h>
#include <iostream>
#include <jack/jack.h>


jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;


/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by 
 * the user (e.g. using Ctrl-C on a unix-ish operating system)
 */
int
process (jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *in, *out;
	
	in = jack_port_get_buffer (input_port, nframes);
	out = jack_port_get_buffer (output_port, nframes);
	memcpy (out, in,
		sizeof (jack_default_audio_sample_t) * nframes);

	return 0;      
}
/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown (void *arg)
{
	exit (1);
}

int main(){
	std::cout << pw_get_host_name() << std::endl;

	const char **ports;
	const char *client_name = "simple";
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;

	return 0;
}
