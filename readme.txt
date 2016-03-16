

==========================================================================

JLT transpiler by PeerHenry 2016

JLT transpiler is a tool that consists of a transpiler tool and a run tool that starts the nodejs server.

==========================================================================

1. TRANSPILER

The transpiler tool will transpile jade, less and typescript to html, css and javascript from a source folder to a build folder.

In order for the transpiler to work correctly you will need:
- a folder called "src" relative to the .exe
- jade compiler installed and available with system command "jade"
- less compiler installed and available with system command "lessc"
- transcript compiler installed and available with system command "tsc"

The three required transpilers with commands can be obtained by installing nodejs, followed by installing with node package manager the following:
npm install -g tsc
npm install -g less
npm install -g jade

running the tool will transpile all *.jade, *.less and *.ts files to a build folder located next to the src folder.
The internal directory structure will be maintained. Other files in the src folder will simply be copied to the build folder.

==========================================================================

2. RUN TOOL

The run tool will start the nodejs server and open localhost on firefox. It takes as arguments the entry .js file and the port it will use.
Without arguments the default settings are: app.js on port 3000

==========================================================================

3. GOAL

These tools were designed to be used with eclipse IDE. Eclipse can be configured to use these programs through the "external tools" feature.

==========================================================================