// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>

using song = std::string;
using artist = std::string;

struct song_info_t{
	artist s_artist;
	int s_length;
	std::list<song>::const_iterator s_recent_it;
	std::list<song>::const_iterator s_playlist_it;
	song_info_t(){}
	song_info_t(artist a, int l, std::list<song>::const_iterator it) : s_artist(a), s_length(l), s_recent_it(it){}
	song_info_t(artist a, int l) : s_artist(a), s_length(l) {}
};

class ipud {
private:
	std::unordered_map<song, song_info_t > player_map;
	std::list<song> playlist_list;
	std::list<song> played_songs_list;
	int total_length_playlist;
public:
	// Leyenda referencias complejidad:
	//
	// C es el numero de canciones, P es el numero de canciones en playlist, CR es el numero de canciones ya reproducidas
	
	ipud() : total_length_playlist(0) {}

	void addSong(song const & song, artist const & artist, int const & length){ // O(1)
		if (!player_map.count(song)){
			auto new_song_it = player_map.insert({ song, { artist, length } });
			player_map[song].s_recent_it = played_songs_list.cend();
			player_map[song].s_playlist_it = playlist_list.cend();
		}
		else
			throw std::domain_error("ERROR");
	}


	void addToPlaylist(song const & song){ // O(1)
		auto it_song = player_map.find(song);
		if (it_song != player_map.cend()){
			if (it_song->second.s_playlist_it == playlist_list.cend()){
				it_song->second.s_playlist_it = playlist_list.insert(playlist_list.cend(), song);
				total_length_playlist += it_song->second.s_length;
			}
		}
		else
			throw std::domain_error("ERROR");
	}


	song current(){ // O(1)
		if (!playlist_list.empty())
			return playlist_list.front();
		else
			throw std::domain_error("ERROR");
	}


	void play(){ // O(1)
		if (!playlist_list.empty()){
			song next_song = playlist_list.front();
			playlist_list.pop_front();
			if (player_map[next_song].s_recent_it != played_songs_list.cend())
				played_songs_list.erase(player_map[next_song].s_recent_it);
			player_map[next_song].s_recent_it = played_songs_list.insert(played_songs_list.cend(), next_song);
			//playlist_list.erase(player_map[next_song].s_playlist_it);
			player_map[next_song].s_playlist_it = playlist_list.cend();
			total_length_playlist -= player_map[next_song].s_length;
		}
		else
			throw std::domain_error("ERROR");
	}
	

	int totalTime(){ // O(1)
		return total_length_playlist;
	}


	std::list<song> recent(int num_recent_songs_to_list){ // O(num_recent_songs_to_list)
		int recent_list_size;
		if (num_recent_songs_to_list <= played_songs_list.size())
			recent_list_size = num_recent_songs_to_list;
		else
			recent_list_size = played_songs_list.size();
		
		std::list<song> recent_songs_list_out;
		auto recent_it = played_songs_list.rbegin();
		for (int k = 0; k < recent_list_size; ++k){
			song next_song = *recent_it;
			recent_songs_list_out.push_back(next_song);
			++recent_it;
		}
		return recent_songs_list_out;
	}


	void deleteSong(song const & song){ // O(1)
		if (player_map.count(song)){
			if (!played_songs_list.empty() && player_map[song].s_recent_it != played_songs_list.cend()){
				played_songs_list.erase(player_map[song].s_recent_it);
				player_map[song].s_recent_it = played_songs_list.cend();
			}
			if (!playlist_list.empty() && player_map[song].s_playlist_it != playlist_list.cend()){
				total_length_playlist -= player_map[song].s_length;
				playlist_list.erase(player_map[song].s_playlist_it);
				player_map[song].s_playlist_it = playlist_list.cend();
			}
			player_map.erase(song);
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	ipud player;
	std::string operacion_tag;
	// leer los datos de la entrada
	std::cin >> operacion_tag;
	if (!std::cin)
		return false;

	while (operacion_tag != "FIN"){
		if (operacion_tag == "addSong"){
			song in_song;
			artist in_artist;
			int in_length;
			std::cin >> in_song >> in_artist >> in_length;
			try{
				player.addSong(in_song, in_artist, in_length);
			}
			catch (std::domain_error err){
				std::cout << "ERROR addSong\n";
			}
		}
		else if (operacion_tag == "addToPlaylist"){
			song in_song;
			std::cin >> in_song;
			try{
				player.addToPlaylist(in_song);
			}
			catch (std::domain_error err){
				std::cout << "ERROR addToPlaylist\n";
			}
		}
		else if (operacion_tag == "current"){
			try{
				player.current();
			}
			catch (std::domain_error err){
				std::cout << "ERROR current\n";
			}
		}
		else if (operacion_tag == "play"){
			try{
				song actual_song = player.current();
				player.play();
				std::cout << "Sonando " << actual_song << "\n";
			}
			catch (std::domain_error err){
				std::cout << "No hay canciones en la lista\n";
			}
		}
		else if (operacion_tag == "totalTime"){
			try{
				std::cout << "Tiempo total " << player.totalTime() << "\n";
			}
			catch (std::domain_error err){
				std::cout << "ERROR totalTime\n";
			}
		}
		else if (operacion_tag == "recent"){
			int num_recent_songs_to_list;
			std::cin >> num_recent_songs_to_list;
			try{
				std::list<song> recent_songs = player.recent(num_recent_songs_to_list);
				if (!recent_songs.empty()){
					std::cout << "Las " << recent_songs.size() << " mas recientes\n";
					for (song const & it_song : recent_songs)
						std::cout << "    " << it_song << "\n";
				}
				else
					std::cout << "No hay canciones recientes\n";
			}
			catch (std::domain_error err){
				std::cout << "ERROR recent\n";
			}
		}
		else if (operacion_tag == "deleteSong"){
			song in_song;
			std::cin >> in_song;
			try{
				player.deleteSong(in_song);
			}
			catch (std::domain_error err){
				std::cout << "ERROR deleteSong\n";
			}
		}
		std::cin >> operacion_tag;
	}
	std::cout << "----\n";
	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}