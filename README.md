<h1 align="center">Search_engine</h1>
<h3 align="center">Search engine for text files</h3>

<p>The search engine is a console application search for text files
and having the ability to configure through the files of the json format.
The solutions applied in it can subsequently integrate the VPOSK engine working on the web.</p>

<h3>Getting started</h3>
clone the repository with the project on your computer with the command:

git clone https://github.com/SergeiVD/Search_engine.git

else copy download archive.zip

After you copy the repository to your computer, go to the project folder:
<ol>
  <li> cd search_engine</li>
if the build folder is not created then create it:
  <li> touch build </li>
  <li> cd build</li>
  <li> cmake ..</li>
  <li> cmake --build .</li>
</ol>
The project is launched by the team:
./search_engine
or by double clicking on the executable file search_engine in the folder build

<p><strong>Compound</strong></p>
<p>The main application classes are</p>
<ul>
  <li>ConverterJSON </li>
  <li>InvertedIndex </li>
  <li>SearchServer </li>
</ul>

<p>Which can be used inside other applications.</p>
<p>To demonstrate the capabilities of the search engine, an auxiliary class <strong>SearchEngine</strong> was developed which is not part of the application and serves only to demonstrate the capabilities</p>

<h3>Application health check</h3>
<p>After launching the application, you will be offered three options for the application:</p>
<ul>
<li> run - the application considers the file config.json which is located in the json folder, it will take search queries from the reguest file. jsion will search for texts that are in a folder called res and save the results of the work to the ansvers.json file</li>
<li> test - the application will run tests to verify the correct operation of the InvertedYIndex and SearchServer classes. The tests themselves are in the google_tests folder.</li>
<li> exit - exit the application.</li>
</ul>

<h3>The principles of the search engine are as follows:</h3>

For this application, configuration data will be stored in a file called config.json, user requests in requests.json, and responses in answers.json. All three files are located in the project directory by default, so you do not need to set a separate path for them.
<ol>
<li> In the configuration file, before the start of the application, the names of the files are set by which the engine will search.</li>
<li> The sketch engine has longed to independently bypass all the files and index them so that then to find the most relevant documents to the love of the search query.</li>
<li> The user sets the request of the JSON file Requests.json. A request is a set of words by which you need to find documents.</li>
<li> The request is transformed into a list of words.</li>
<li> The index is looking for those documents on which all these words are found.</li>
<li> The results of the search are ranked, sorted and given to the user, the maximum number of possible documents in the answer is set in the configuration file.</li>
<li> At the end of the program, it forms the fileswers.json file, in which it records the search results.</li>
</ol>


<p><strong>Configuration file config.json.</strong></p>

<p>Without it, the application cannot be launched. It contains the name of the search engine, its version, the database update time (with what frequency it is necessary to re-index the database, re-upload files and calculate their search rating), the maximum number of options in the answer (if not specified, then the value is chosen equal to five).
</p>

An example of a config.json file description:
<p>{</p>
  <p>"config":</p>
              <p>{</p>
                 <p>"name": "SkillboxSearchEngine",</p>
                 <p>"version": "0.1",</p>
                 <p>"max_responses": 5</p>
              <p>},</p>
              <p>"files":</p>
                       <p>[</p>
                           <p>"../resources/file001.txt",</p>
                           <p>"../resources/file002.txt",</p>
                           <p>"../resources/file003.txt",</p>
                           <p>"../resources/file004.txt",</p>
                           <p>...</p>
                       <p>]</p>
  <p>}</p>
  </p>
  
  <p>
Let's take a closer look at each field of the config.json file
<ul>
 <li>config—general information, without which the application will not start. If this field is absent, then at startup the program should throw an exception and display the error config file is empty in the text console. If the config.json file itself is missing, then you must throw an exception and display the error configfile is missing.
 </li>
 <li>name—field with the name of the search engine. It can be anything: you can come up with a name for the search engine yourself. Information from this  field must be displayed when starting the Starting application.
 </li>
 <li>version is a field with the version number of the search engine. You can check later. If the version field does not match the version of the application itself, then the config.json has incorrect fileversion error should be thrown.</li>
 <li>max_responses is a field that defines the maximum number of responses per request.</li>
 <li>files contains the paths to the files to be searched. The files list contains the paths to the files.</li>
 <li><path to file>(“../resorces/file001.txt”) is the path to the file. Subsequently, its contents must be searched. If the file does not exist on this    path, then the corresponding error is displayed on the screen, but the program does not stop. In this case, each document contains no more than 1000 words with a maximum length of 100 characters each. Words consist of lowercase Latin letters and are separated by one or more spaces</li>
</ul>
  </p>
  
<p><strong>File with requests requests.json</strong></p>
It contains requests that the search engine needs to process. An example of a requests.json file description:
<p>{</p>
     <p>"requests": </p>
                  <p>[</p>
                       <p>"some words..",</p>
                       <p>"some words..",</p>
                       <p>"some words..",</p>
                       <p>"some words..",</p>
                       <p>...</p>
                      <p>]</p>
     <p>}</p>
     
 <p>Let's analyze each field of the config.json file in more detail</p>
 <ul>
 <li>requests consists of a list of requests to be processed by the search engine. The field contains no more than 1000 queries, each of which includes from one to ten words.</li>
<li><query content>(“some words”) — search query, a set of words separated by one or more spaces. They need to be searched. All words are composed of lowercase Latin letters.</li>
  </ul>

<p><strong>The file with responses to requests answers.json.</strong></p>
<p>It records the results of the search engine. If this file does not exist in the directory with the project when starting the application, then it must be created. If the file already exists, then it is necessary to delete all its contents.</p>

<p>An example of a description of the answers.json file:</p>

<p>{</p>
<p>"answers": </p>
<p>{"request001": {</p>
<p>"result": </p>
<p>"true",</p>
<p>"relevance":</p> 
<p>{"docid": 0, </p>
<p>“rank” : 0.989,</p>
<p>"docid": 1, </p>
<p>“rank” : 0.897,</p>
<p>"docid": 2, </p>
<p>“rank” : 0.750,</p>
<p>"docid": 3,</p>
<p>“rank” : 0.670,</p>
<p>"docid": 4,</p>
<p>“rank” : 0.561</p>
<p>}</p>
<p>},</p>
<p>"request002": </p>
<p>{"result": "true",</p>
<p>"docid": 0, </p>
<p>“rank” : 0.769</p>
<p>},</p>
<p>"request003": </p>
<p>{"result": "false"}</p>
<p>}</p>
<p>}</p>

<ul>
  <p>Consider each field of the answers.json file:</p>
  <li>answers is the base field in this file that contains responses to queries.</li>
<li>request001 ... 003 — ID of the request on which the response was generated. The request ID is generated automatically in the order in which the requests are in the requests field of the requests.json file.
  <p>For example:</p>
  <p>"requests":</p>
  <p>                  [</p>
  <p>                      "some words..", for this string the request id will be "request001"</p>
  <p>"some words..", for this string the request id will be "request002"</p>
  <p>"some words..", for this string the request id will be "request003"</p>
  <p>"some words..", for this string the request id will be "request004"</p>
  <p>...</p>
  <p>]</p>
</li>
<li>result – query search result. If it evaluates to true, then at least one document was found for the submitted query. If the result is false, then no documents were found. Then there are no other fields in the response to this request.</li>
<li>relevance is included in the answers.json file if more than one document was found for this query. The following matches the response rating and the name of the id of the document being searched:</li>
<li><Document ID>("docid") — ID of the document in which the response to the query was found. It is generated automatically when indexing all documents based on the order in which the documents are located in the files field in the config.json file.
For example, if in the config.json field, the files field contains:
  <p>"files":</p>
           <p>["../resources/file001.txt", for this file docid will be equal to 0</p>
            <p>"../resources/file002.txt", for this file docid will be equal to 1</p>
            <p>"../resources/file003.txt", for this file docid will be equal to 2</p>
            <p>"../resources/file004.txt", for this file docid will be equal to 3</p>
            <p> ...</p>
            <p>]</p>
</li>
<li><answer rank>(“rank”) — rank or search rating. This number indicates how good the document is for a given query. In the response, document id's are arranged in order of decreasing search ranking.</li>
</ul>
