var express = require('express');
var app = express();
var mongoose = require('mongoose');


var mongoOptions = {
	user: "herbot",
	password: "password"
}

mongoose.conenct('mongodb://@ds039095.mongolab.com:39095/heroku_dcsmg1bn', mongoOptions);
var db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function(){
	console.log('Connected to mongo');
});

//SCHEMA

var Plant = new mongoose.Schema({
	waterLevel: String
},
{
	strict: false
});


app.set('port', (process.env.PORT || 5000));


app.get('/*', function(request, response) {
	
	   var url = request.originalUrl;
	   response.send(200);

	   var plant = new Plant({
	   	waterLevel: url
	   });

	   plant.save(function(err){
	   	if(err){
			console.log('Save was unsuccesful:' +  err);
		}
	   });
});

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});


