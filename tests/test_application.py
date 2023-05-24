import json
import pytest
from LEDController.app import app

@pytest.fixture
def client():
    return app.test_client()

def test_response(client):
    assert 1
