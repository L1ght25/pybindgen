==================
pytest-localserver
==================

pytest-localserver is a plugin for the `pytest`_ testing framework which enables
you to test server connections locally.

Sometimes `monkeypatching`_ ``urllib2.urlopen()`` just does not cut it, for
instance if you work with ``urllib2.Request``, define your own openers/handlers
or work with ``httplib``. In these cases it may come in handy to have an HTTP
server running locally which behaves just like the real thing [1]_. Well, look
no further!

Quickstart
==========

Let's say you have a function to scrape HTML which only required to be pointed
at a URL ::

    import requests
    def scrape(url):
        html = requests.get(url).text
        # some parsing happens here
        # ...
        return result

You want to test this function in its entirety without having to rely on a
remote server whose content you cannot control, neither do you want to waste
time setting up a complex mechanism to mock or patch the underlying Python
modules dealing with the actual HTTP request (of which there are more than one
BTW). So what do you do?

You simply use pytest's `funcargs feature`_ and simulate an entire server
locally! ::

    def test_retrieve_some_content(httpserver):
        httpserver.serve_content(open('cached-content.html').read())
        assert scrape(httpserver.url) == 'Found it!'

What happened here is that for the duration of your tests an HTTP server is
started on a random port on localhost which will serve the content you tell it
to and behaves just like the real thing.

The added bonus is that you can test whether your code behaves gracefully if
there is a network problem::

    def test_content_retrieval_fails_graciously(httpserver):
        httpserver.serve_content('File not found!', 404)
        pytest.raises(ContentNotFoundException, scrape, httpserver.url)

The same thing works for SMTP servers, too::

    def test_sending_some_message(smtpserver):
        mailer = MyMailer(host=smtpserver.addr[0], port=smtpserver.addr[1])
        mailer.send(to='bob@example.com', from_='alice@example.com',
            subject='MyMailer v1.0', body='Check out my mailer!')
        assert len(smtpserver.outbox)==1

Here an SMTP server is started which accepts e-mails being sent to it. The
nice feature here is that you can actually check if the message was received
and what was sent by looking into the smtpserver's ``outbox``.

It is really that easy!

Available funcargs
==================

Here is a short overview of the available funcargs. For more details I suggest
poking around in the code itself.

``httpserver``
    provides a threaded HTTP server instance running on localhost. It has the
    following attributes:

    * ``code`` - HTTP response code (int)
    * ``content`` - content of next response (str)
    * ``headers`` - response headers (dict)

    Once these attribute are set, all subsequent requests will be answered with
    these values until they are changed or the server is stopped. A more
    convenient way to change these is ::

        httpserver.serve_content(content=None, code=200, headers=None)

    The server address can be found in property

    * ``url``

    which is the string representation of tuple ``server_address`` (host as str,
    port as int).

    If you want to check which form fields have been POSTed, Try ::

        httpserver.serve_content(..., show_post_vars=True)

    which will display them as parsable text.

    If you need to inspect the requests sent to the server, a list of all
    received requests can be found in property

    * ``requests``

    which is a list of ``werkzeug.wrappers.Request`` objects.

``httpsserver``
    is the same as ``httpserver`` only with SSL encryption.

``smtpserver``
    provides a threaded instance of ``smtpd.SMTPServer`` runnning on localhost.
    It has the following attributes:

    * ``addr`` - server address as tuple (host as str, port as int)
    * ``outbox`` - list of ``email.message.Message`` instances received.

Using your a WSGI application as test server
============================================

As of version 0.3 you can now use a `WSGI application`_ to run on the test
server ::

    from pytest_localserver.http import WSGIServer

    def simple_app(environ, start_response):
        """Simplest possible WSGI application"""
        status = '200 OK'
        response_headers = [('Content-type', 'text/plain')]
        start_response(status, response_headers)
        return ['Hello world!\n']

    @pytest.fixture
    def testserver(request):
        """Defines the testserver funcarg"""
        server = WSGIServer(application=simple_app)
        server.start()
        request.addfinalizer(server.stop)
        return server

    def test_retrieve_some_content(testserver):
        assert scrape(testserver.url) == 'Hello world!\n'

Have a look at the following page for more information on WSGI:
http://wsgi.readthedocs.org/en/latest/learn.html

Download and Installation
=========================

You can install the plugin by running ::

    pip install pytest-localserver

Alternatively, get the latest stable version from `PyPI`_ or the latest
`bleeding-edge`_ from Github.

License and Credits
===================

This plugin is released under the MIT license. You can find the full text of
the license in the LICENSE file.

Copyright (C) 2010-2021 Sebastian Rahlf and others (see AUTHORS).

Some parts of this package is based on ideas or code from other people:

- I borrowed some implementation ideas for the httpserver from `linkchecker`_.
- The implementation for the SMTP server is based on the `Mailsink recipe`_ by
  Adam Feuer, Matt Branthwaite and Troy Frever.
- The HTTPS implementation is based on work by `Sebastien Martini`_.

Thanks guys!

Development and future plans
============================

Feel free to clone the repository and add your own changes. Pull requests are
always welcome!::

    git clone https://github.com/pytest-dev/pytest-localserver

If you find any bugs, please file a `report`_.

Test can be run with tox. Note that you need virtualenv<1.8 to run tests for
Python 2.4.

I already have a couple of ideas for future versions:

* support for FTP, SSH (maybe base all on twisted?)
* making the SMTP outbox as convenient to use as ``django.core.mail.outbox``
* add your own here!

----

.. [1] The idea for this project was born when I needed to check that `a piece
       of software`_ behaved itself when receiving HTTP error codes 404 and 500.
       Having unsuccessfully tried to mock a server, I stumbled across
       `linkchecker`_ which uses a the same idea to test its internals.

.. _monkeypatching: http://pytest.org/latest/monkeypatch.html
.. _pytest: http://pytest.org/
.. _funcargs feature: http://pytest.org/latest/funcargs.html
.. _linkchecker: http://linkchecker.sourceforge.net/
.. _WSGI application: http://www.python.org/dev/peps/pep-0333/
.. _PyPI: http://pypi.python.org/pypi/pytest-localserver/
.. _bleeding-edge: https://github.com/pytest-dev/pytest-localserver
.. _report: https://github.com/pytest-dev/pytest-localserver/issues/
.. _tox: http://testrun.org/tox/
.. _a piece of software: http://pypi.python.org/pypi/python-amazon-product-api/
.. _Mailsink recipe: http://code.activestate.com/recipes/440690/
.. _Sebastien Martini: http://code.activestate.com/recipes/442473/
