# CiteGraph

Explore/displays a topological map (a graph) of journal articles and their interconnectivity via citations.
Add visual feedback to indicate impact of each journal (citation count etc.) and strength of connection (similarity/number of times cited in journal body)

Dependencies/Technologies used:
- libcurl     (accessing CrossRef RESTful webservice via queries)
- rapidjson   (parsing output of queries into CiteGraph data structures)
- SDL2        (framework for I/O, windowing, video output via OpenGL handle etc.)
- OpenGL      (Graphics api)
- GLUT        (For fonts)

Once DOI of interest is determined, use following line of C++ code to resolve:
system("start https://doi.org/<DOI>");

Also, use multithreading to asynchonously process data and handle user input/display output etc.
