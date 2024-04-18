PY3TEST()

PEERDIR(
    contrib/python/oauthlib
    contrib/python/mock
    contrib/python/PyJWT
    contrib/python/blinker
)

PY_SRCS(
    NAMESPACE tests
    unittest/__init__.py
)

TEST_SRCS(
    __init__.py
    oauth1/__init__.py
    oauth1/rfc5849/__init__.py
    oauth1/rfc5849/endpoints/__init__.py
    oauth1/rfc5849/endpoints/test_access_token.py
    oauth1/rfc5849/endpoints/test_authorization.py
    oauth1/rfc5849/endpoints/test_base.py
    oauth1/rfc5849/endpoints/test_request_token.py
    oauth1/rfc5849/endpoints/test_resource.py
    oauth1/rfc5849/endpoints/test_signature_only.py
    oauth1/rfc5849/test_client.py
    oauth1/rfc5849/test_parameters.py
    oauth1/rfc5849/test_request_validator.py
    oauth1/rfc5849/test_signatures.py
    oauth1/rfc5849/test_utils.py
    oauth2/__init__.py
    oauth2/rfc6749/__init__.py
    oauth2/rfc6749/clients/__init__.py
    oauth2/rfc6749/clients/test_backend_application.py
    oauth2/rfc6749/clients/test_base.py
    oauth2/rfc6749/clients/test_legacy_application.py
    oauth2/rfc6749/clients/test_mobile_application.py
    oauth2/rfc6749/clients/test_service_application.py
    oauth2/rfc6749/clients/test_web_application.py
    oauth2/rfc6749/endpoints/__init__.py
    oauth2/rfc6749/endpoints/test_base_endpoint.py
    oauth2/rfc6749/endpoints/test_client_authentication.py
    oauth2/rfc6749/endpoints/test_credentials_preservation.py
    oauth2/rfc6749/endpoints/test_error_responses.py
    oauth2/rfc6749/endpoints/test_extra_credentials.py
    oauth2/rfc6749/endpoints/test_introspect_endpoint.py
    oauth2/rfc6749/endpoints/test_metadata.py
    oauth2/rfc6749/endpoints/test_resource_owner_association.py
    oauth2/rfc6749/endpoints/test_revocation_endpoint.py
    oauth2/rfc6749/endpoints/test_scope_handling.py
    oauth2/rfc6749/endpoints/test_utils.py
    oauth2/rfc6749/grant_types/__init__.py
    oauth2/rfc6749/grant_types/test_authorization_code.py
    oauth2/rfc6749/grant_types/test_client_credentials.py
    oauth2/rfc6749/grant_types/test_implicit.py
    oauth2/rfc6749/grant_types/test_refresh_token.py
    oauth2/rfc6749/grant_types/test_resource_owner_password.py
    oauth2/rfc6749/test_parameters.py
    oauth2/rfc6749/test_request_validator.py
    oauth2/rfc6749/test_server.py
    oauth2/rfc6749/test_tokens.py
    oauth2/rfc6749/test_utils.py
    oauth2/rfc8628/__init__.py
    oauth2/rfc8628/clients/__init__.py
    oauth2/rfc8628/clients/test_device.py
    openid/__init__.py
    openid/connect/__init__.py
    openid/connect/core/__init__.py
    openid/connect/core/endpoints/__init__.py
    openid/connect/core/endpoints/test_claims_handling.py
    openid/connect/core/endpoints/test_openid_connect_params_handling.py
    openid/connect/core/endpoints/test_userinfo_endpoint.py
    openid/connect/core/grant_types/__init__.py
    openid/connect/core/grant_types/test_authorization_code.py
    openid/connect/core/grant_types/test_base.py
    openid/connect/core/grant_types/test_dispatchers.py
    openid/connect/core/grant_types/test_hybrid.py
    openid/connect/core/grant_types/test_implicit.py
    openid/connect/core/test_request_validator.py
    openid/connect/core/test_server.py
    openid/connect/core/test_tokens.py
    test_common.py
    test_uri_validate.py
)

NO_LINT()

END()
