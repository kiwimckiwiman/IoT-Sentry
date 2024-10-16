from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import func
app = Flask(__name__)

# Replace with your MariaDB server URL, username, and password
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://pi:password@localhost/sensor_db'

db = SQLAlchemy(app)

class Settings(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    sentry_mode = db.Column(db.String(10))
    sentry_range = db.Column(db.String(10))
    active_time = db.Column(db.String(10))

class Actions(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    U = db.Column(db.String(10))
    D = db.Column(db.String(10))
    L = db.Column(db.String(10))
    R = db.Column(db.String(10))
    S = db.Column(db.String(10))

@app.route('/')
def index():
    current_settings = Settings.query.first()
    all_actions = Actions.query.first()
    return render_template('index.html', settings=current_settings, actions=all_actions)

@app.route('/update_settings', methods=['POST'])
def update_settings():
   new_sentry_mode = request.form['sentry_mode']
   new_sentry_range = request.form['sentry_range']
   new_active_time = request.form['active_time']

   current_settings = Settings.query.first()
   current_settings.sentry_mode = new_sentry_mode
   current_settings.sentry_range = new_sentry_range
   current_settings.active_time = new_active_time
   db.session.commit()

   return redirect(url_for('index'))
