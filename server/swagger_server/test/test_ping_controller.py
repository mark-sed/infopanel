# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.test import BaseTestCase


class TestPingController(BaseTestCase):
    """PingController integration test stubs"""

    def test_ping(self):
        """Test case for ping

        Ping
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/ping',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
