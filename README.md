# Decoder

* Simple decoder for analyzing single files at a time
* The default output is set under bbox,
    * 'std::string output_path = "/bbox/commissioning/INTT/hit_files/";' (line 9 of main.cc)
    * You can change it if you like but I insist on keeping it somewhere under '/bbox/commissioning/INTT/'
* The analysis is event based instead of hit-based, so empty events are easy to identify
* I'm including some additional hit-based branches in the output, they are some unfiltered iValue
  retrivals
