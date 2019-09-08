package main

import (
	"log"
	"net/http"
	"regexp"
)

var wasmFile = regexp.MustCompile("\\.wasm$")
var jsFile = regexp.MustCompile("\\.js$")
var fs = http.FileServer(http.Dir("./"))

func server(w http.ResponseWriter, r *http.Request) {
	uri := r.RequestURI
	if wasmFile.MatchString(uri) {
		w.Header().Set("Content-Type", "application/wasm")
	}
	if jsFile.MatchString(uri) {
		w.Header().Set("Content-Type", "text/javascript")
	}
	fs.ServeHTTP(w, r)
}

func main() {

	http.HandleFunc("/", server)
	log.Println("Listening at http://localhost:4242")
	http.ListenAndServe(":4242", nil)
}
