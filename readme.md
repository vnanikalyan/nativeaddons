1. Create binding.gyp giving the source and target values

# Install node-gyp ; npm install node-gyp -g
2. Run: node-gyp configure
3. Run: node-gyp build/rebuild

Once the build is successful then <filename.node> will be generated in build/Release folder
You can copy the same to the root folder and import it as follows

const nani = require('./filename) //No need of the .node extension