package main

import (
    // "encoding/json"
    "fmt"
    "io/ioutil"
    "log"
    "net/http"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
    body, _ := ioutil.ReadAll(r.Body)
	fmt.Println(string(body))

	err := json.NewDecoder(r.Body).Decode(&u)
	if err != nil {
		http.Error(w, err.Error(), 400)
	}
}
func main() {
    http.HandleFunc("/hello", helloHandler)
    err := http.ListenAndServe(":8080", nil) 
    if err != nil {
        log.Fatal("ListenAndServe: ", err.Error())
    }
}