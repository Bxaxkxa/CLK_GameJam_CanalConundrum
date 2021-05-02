from better_profanity import profanity
from flask import Flask, render_template, jsonify, request
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import hashlib

magic_salt = 'this_is_a_magic_string5828177577217725'

app = Flask(__name__)

project_id = 'clkjam'
cred = credentials.ApplicationDefault()
firebase_admin.initialize_app(cred, {
  'projectId': project_id,
})

db = firestore.client()

@app.route('/')
def root():
    return render_template('index.html')

@app.route('/hiscores', methods=['GET', 'POST'])
def hiscores():
    if request.method == 'POST':
        return post_hiscores()
    else:
        return get_hiscores()

def get_hiscores():
    results = db.collection('scores').order_by('time', direction=firestore.Query.DESCENDING).limit(10).stream()
    ret = []
    for row in results:
        r = row.to_dict()
        ret.append({'name':r['name'], 'time':r['time']})
    return jsonify(ret)

def post_hiscores():
    # make sure all vars provided
    if not request.form['name'] or not request.form['time'] or not request.form['magic']:
        print('missing field')
        abort(500)

    name = str(request.form['name'])
    time = int(str(request.form['time']))
    magic = str(request.form['magic'])

    # make sure name has no profanity
    if profanity.contains_profanity(name):
        print('contains profanity')
        abort(500)

    # very basic anti-cheat
    message = name + ',' + str(time) + ',' + magic_salt
    digest = hashlib.sha256(message.encode()).hexdigest()
    if digest != magic:
        print('invalid hash')
        abort(500)

    doc_ref = db.collection('scores').document()
    doc_ref.set({
        'name': name,
        'time': time
    })

    return jsonify({'name':name, 'time':time})

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)