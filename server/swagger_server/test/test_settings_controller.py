# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.models.scheduler import Scheduler  # noqa: E501
from swagger_server.test import BaseTestCase


class TestSettingsController(BaseTestCase):
    """SettingsController integration test stubs"""

    def test_set_currency(self):
        """Test case for set_currency

        Sets up prefered currency
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/settings/currency/{name}'.format(name='name_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_finhub_key(self):
        """Test case for set_finhub_key

        Sets up Finhub key
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/settings/finhubKey/{key}'.format(key='key_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_polygon_key(self):
        """Test case for set_polygon_key

        Sets up Finhub key
        """
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/settings/polygonKey/{key}'.format(key='key_example'),
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_set_scheduler(self):
        """Test case for set_scheduler

        Sets up scheduler
        """
        scheduler = Scheduler()
        response = self.client.open(
            '/sedlacek/StockPanel/1.0.0/settings/scheduler',
            method='POST',
            data=json.dumps(scheduler),
            content_type='application/json')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
