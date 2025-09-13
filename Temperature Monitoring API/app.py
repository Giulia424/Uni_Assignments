from flask import Flask, request, jsonify, make_response
from flask_sqlalchemy import SQLAlchemy
from os import environ
import datetime
from datetime import timezone


app = Flask(__name__, )
app.config['SQLALCHEMY_DATABASE_URI'] = environ.get('DB_URL')
db = SQLAlchemy(app)
class Country(db.Model):
    __tablename__ = 'countries'

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), nullable=False,unique=True)
    lat = db.Column(db.Double, nullable=False)
    lon = db.Column(db.Double, nullable=False)

    def json(self):
        return {'id': self.id, 'nume': self.name, 'lat': self.lat, 'lon': self.lon}
    
    
class City(db.Model):
    __tablename__ = 'cities'

    id = db.Column(db.Integer, primary_key=True)
    country_id = db.Column(db.Integer, db.ForeignKey('countries.id'), nullable=False)
    name = db.Column(db.String(50), nullable=False)
    lat = db.Column(db.Double, nullable=False)
    lon = db.Column(db.Double, nullable=False)

    def json(self):
        return {'id': self.id,  'idTara': self.country_id, 'nume': self.name, 'lat': self.lat, 'lon': self.lon}

__table_args__ = (
        db.UniqueConstraint('id_tara', 'nume_oras', name='unique_id_tara_nume_oras'),
    )

class Temperature(db.Model):
    __tablename__ = 'temperatures'

    id = db.Column(db.Integer, primary_key=True)
    temperature = db.Column(db.Double, nullable=False)
    timestamp = db.Column(db.DateTime, nullable=False)
    city_id = db.Column(db.Integer, db.ForeignKey('cities.id'), nullable=False)

    def json(self):
        return {'id': self.id, 'valoare': self.temperature, 'timestamp': self.timestamp}

__table_args__ = (
        db.UniqueConstraint('idOras', 'timestamp', name='unique_idOras_timestamp'),
    )

with app.app_context():
    db.drop_all()
    db.create_all()

@app.route('/test', methods=['GET'])
def test():
    return make_response(jsonify({'message': 'test!'}), 200)

#400 (Bad Request), 404 (Not Found) și 409 (Conflict)

# add country
@app.route('/api/countries', methods=['POST'])
def create_country():
    try:
        data = request.get_json()
        country = Country(name=data['nume'], lat=data['lat'], lon=data['lon'])
        if Country.query.filter_by(name=data['nume']).first():
            return make_response(jsonify({'message': 'country already exists'}), 409)
        db.session.add(country)
        db.session.commit()
        return make_response(jsonify({'id': country.id}), 201)

    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)
    
# get all countries
@app.route('/api/countries', methods=['GET'])
def get_countries():
    countries = Country.query.all()
    return make_response(jsonify([country.json() for country in countries]), 200)

# update country by id
@app.route('/api/countries/<int:id>', methods=['PUT'])
def update_country(id):
    try:
        country = Country.query.filter_by(id=id).first()
        if country:
            data = request.get_json()
            if id != data['id']:
                return make_response(jsonify({'message':  "bad request"}), 400)
            if Country.query.filter(Country.id != id, Country.name == data['nume']).first():
                return make_response(jsonify({'message': 'country already exists'}), 409)
            country.name = data['nume']
            country.lat = data['lat']
            country.lon = data['lon']
            db.session.commit()
            return make_response(jsonify({'message': "country successfully updated"}), 200)
        else:
            return make_response(jsonify({'message':  "country not found"}), 404)
    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)

# delete country by id
@app.route('/api/countries/<int:id>', methods=['DELETE'])
def delete_country(id):
    try:
        country = Country.query.filter_by(id=id).first()
        if country:
            db.session.delete(country)
            cities = City.query.filter_by(country_id=id).all()
            for city in cities:
                db.session.delete(city)
            db.session.commit()
            return make_response(jsonify({'message': 'country succesfully deleted'}),200)
        return make_response(jsonify({'message': 'country not found'}),404) 
    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)



# add city
@app.route('/api/cities', methods=['POST'])
def create_city():
    try:
        data = request.get_json()
        if not Country.query.filter_by(id=data['idTara']).first():
            return make_response(jsonify({'message': 'country not found'}), 404)
        if City.query.filter_by(name=data['nume'], country_id=data['idTara']).first():
            return make_response(jsonify({'message': 'city already exists'}), 409)       
        city = City(country_id=data['idTara'], name=data['nume'], lat=data['lat'], lon=data['lon'])
        db.session.add(city)
        db.session.commit()
        return make_response(jsonify({'id': city.id}), 201)

    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)

# get all cities
@app.route('/api/cities', methods=['GET'])
def get_cities():
    cities = City.query.all()
    return make_response(jsonify([city.json() for city in cities]), 200)

#get city by country_id 
@app.route('/api/cities/country/<int:idTara>', methods=['GET'])
def get_cities_by_country(idTara):
    cities = City.query.filter_by(country_id=idTara).all()
    return make_response(jsonify([city.json() for city in cities]), 200)

# update city by id
@app.route('/api/cities/<int:id>', methods=['PUT'])
def update_city(id):
    try:
        city = City.query.filter_by(id=id).first()
        if city:
            data = request.get_json()
            if id != data['id']:
                return make_response(jsonify({'message':  "bad request"}), 400)
            if City.query.filter(City.id != id, City.country_id==data['idTara'], City.name==data['nume']).first():
                return make_response(jsonify({'message': 'city already exists'}), 409)
            city.country_id = data['idTara']
            city.name = data['nume']
            city.lat = data['lat']
            city.lon = data['lon']
            db.session.commit()
            return make_response(jsonify({'message': "city successfully updated"}), 200)
        else:
            return make_response(jsonify({'message':  "city not found"}), 404)

    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)

# delete city by id
@app.route('/api/cities/<int:id>', methods=['DELETE'])
def delete_city(id):
    try:
        city = City.query.filter_by(id=id).first()
        if city:
            db.session.delete(city)
            temperatures = Temperature.query.filter_by(city_id=id).all()
            for temperature in temperatures:
                db.session.delete(temperature)
            db.session.commit()
            return make_response(jsonify({'message': 'city succesfully deleted'}),200)
        return make_response(jsonify({'message': 'city not found'}),404)
    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)


# add temperature
@app.route('/api/temperatures', methods=['POST'])
def create_temperature():
    try:
        data = request.get_json()
        if not City.query.filter_by(id=data['idOras']).first():
            return make_response(jsonify({'message': 'city not found'}), 404)
        time=datetime.datetime.now(timezone.utc)
        if Temperature.query.filter_by(city_id=data['idOras'], timestamp=time ).first():
            return make_response(jsonify({'message': 'temperature already exists'}), 409)
        temperature = Temperature(city_id=data['idOras'],temperature=data['valoare'], timestamp=time)
        db.session.add(temperature)
        db.session.commit()
        return make_response(jsonify({'id': temperature.id}), 201)

    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)

# get temperature by long, lat and timestamp 
@app.route('/api/temperatures', methods=['GET'])
def get_temperatures():
    lat = request.args.get('lat')
    lon = request.args.get('lon')
    initial = request.args.get('from')
    final = request.args.get('until')
    query = Temperature.query.join(City)
    if lat: 
        lat = float(lat)
        query = query.filter(City.lat == lat)
    if lon:
        lon = float(lon)
        query = query.filter(City.lon == lon)
    if initial:
        initial = datetime.datetime.strptime(initial, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp >= initial)
    if final:
        final = datetime.datetime.strptime(final, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp <= final)
    query = query.all()
    return make_response(jsonify([temperature.json() for temperature in query]), 200)



# get temperature by city, initial and final timestamp 
@app.route('/api/temperatures/cities/<int:idOras>', methods=['GET'])
def get_temperatures_by_city(idOras):
    initial = request.args.get('from')
    final = request.args.get('until')
    query = Temperature.query.join(City).filter(City.id == idOras)
    if initial:
        initial = datetime.datetime.strptime(initial, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp >= initial)
    if final:
        final = datetime.datetime.strptime(final, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp <= final)
    query = query.all()
    return make_response(jsonify([temperature.json() for temperature in query]), 200)


# get temperature by country, initial and final timestamp
@app.route('/api/temperatures/countries/<int:idTara>', methods=['GET'])
def get_temperatures_by_country(idTara):
    initial = request.args.get('from')
    final = request.args.get('until')
    query = Temperature.query.join(City).filter(City.country_id == idTara)
    if initial:
        initial = datetime.datetime.strptime(initial, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp >= initial)
    if final:
        final = datetime.datetime.strptime(final, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp <= final)
    query = query.all()
    return make_response(jsonify([temperature.json() for temperature in query]), 200)

# edit temperature
@app.route('/api/temperatures/<int:id>', methods=['PUT'])
def update_temperature(id):
    try:
        temperature = Temperature.query.filter_by(id=id).first()
        if temperature:
            data = request.get_json()
            if id != data['id']:
                return make_response(jsonify({'message':  "bad request"}), 400)
            time=datetime.datetime.now(timezone.utc)
            if Temperature.query.filter(Temperature.id != id, Temperature.city_id==data['idOras'], Temperature.timestamp==time).first():
                return make_response(jsonify({'message': 'temperature already exists'}), 409)
           
            temperature.temperature = data['valoare']
            temperature.city_id = data['idOras']
            db.session.commit()
            return make_response(jsonify({'message': "temperature successfully updated"}), 200)
        else:
            return make_response(jsonify({'message':  "temperature not found"}), 404)

    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)

# delete temperature by id
@app.route('/api/temperatures/<int:id>', methods=['DELETE'])
def delete_temperature(id):
    try:
        temperature = Temperature.query.filter_by(id=id).first()
        if temperature:
            db.session.delete(temperature)
            db.session.commit()
            return make_response(jsonify({'message': 'temperature succesfully deleted'}),200)
        return make_response(jsonify({'message': 'temperature not found'}),404)
    except Exception as e:
        return make_response(jsonify({'message':  "bad request"}), 400)


app.run(port=4000, host='0.0.0.0', debug=True)