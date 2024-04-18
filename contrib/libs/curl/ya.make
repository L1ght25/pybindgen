# Generated by devtools/yamaker from nixpkgs 22.11.

LIBRARY()

LICENSE(
    BSD-3-Clause AND
    ISC AND
    Public-Domain AND
    curl
)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(8.5.0)

ORIGINAL_SOURCE(https://github.com/curl/curl/releases/download/curl-8_5_0/curl-8.5.0.tar.bz2)

PEERDIR(
    contrib/libs/libc_compat
    contrib/libs/nghttp2
    contrib/libs/openssl
    contrib/libs/zlib
)

IF (NOT EXPORT_CMAKE)
    ADDINCL(
        contrib/libs/c-ares/include
    )
ENDIF()

ADDINCL(
    GLOBAL contrib/libs/curl/include
    contrib/libs/curl/lib
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

DEFAULT(ARCADIA_CURL_DNS_RESOLVER ARES)

CFLAGS(
    GLOBAL -DCURL_STATICLIB
    -DBUILDING_LIBCURL
    -DHAVE_CONFIG_H
    -DARCADIA_CURL_DNS_RESOLVER_${ARCADIA_CURL_DNS_RESOLVER}
)

IF (ARCADIA_CURL_DNS_RESOLVER == ARES)
    PEERDIR(
        contrib/libs/c-ares
    )
ENDIF()

IF (OS_DARWIN)
    LDFLAGS(
        -framework
        SystemConfiguration
    )
ENDIF()

SRCS(
    lib/altsvc.c
    lib/amigaos.c
    lib/asyn-ares.c
    lib/asyn-thread.c
    lib/base64.c
    lib/bufq.c
    lib/bufref.c
    lib/c-hyper.c
    lib/cf-h1-proxy.c
    lib/cf-h2-proxy.c
    lib/cf-haproxy.c
    lib/cf-https-connect.c
    lib/cf-socket.c
    lib/cfilters.c
    lib/conncache.c
    lib/connect.c
    lib/content_encoding.c
    lib/cookie.c
    lib/curl_addrinfo.c
    lib/curl_des.c
    lib/curl_endian.c
    lib/curl_fnmatch.c
    lib/curl_get_line.c
    lib/curl_gethostname.c
    lib/curl_gssapi.c
    lib/curl_memrchr.c
    lib/curl_multibyte.c
    lib/curl_ntlm_core.c
    lib/curl_ntlm_wb.c
    lib/curl_path.c
    lib/curl_range.c
    lib/curl_rtmp.c
    lib/curl_sasl.c
    lib/curl_sspi.c
    lib/curl_threads.c
    lib/curl_trc.c
    lib/dict.c
    lib/doh.c
    lib/dynbuf.c
    lib/dynhds.c
    lib/easy.c
    lib/easygetopt.c
    lib/easyoptions.c
    lib/escape.c
    lib/file.c
    lib/fileinfo.c
    lib/fopen.c
    lib/formdata.c
    lib/ftp.c
    lib/ftplistparser.c
    lib/getenv.c
    lib/getinfo.c
    lib/gopher.c
    lib/hash.c
    lib/headers.c
    lib/hmac.c
    lib/hostasyn.c
    lib/hostip.c
    lib/hostip4.c
    lib/hostip6.c
    lib/hostsyn.c
    lib/hsts.c
    lib/http.c
    lib/http1.c
    lib/http2.c
    lib/http_aws_sigv4.c
    lib/http_chunks.c
    lib/http_digest.c
    lib/http_negotiate.c
    lib/http_ntlm.c
    lib/http_proxy.c
    lib/idn.c
    lib/if2ip.c
    lib/imap.c
    lib/inet_ntop.c
    lib/inet_pton.c
    lib/krb5.c
    lib/ldap.c
    lib/llist.c
    lib/macos.c
    lib/md4.c
    lib/md5.c
    lib/memdebug.c
    lib/mime.c
    lib/mprintf.c
    lib/mqtt.c
    lib/multi.c
    lib/netrc.c
    lib/nonblock.c
    lib/noproxy.c
    lib/openldap.c
    lib/parsedate.c
    lib/pingpong.c
    lib/pop3.c
    lib/progress.c
    lib/psl.c
    lib/rand.c
    lib/rename.c
    lib/rtsp.c
    lib/select.c
    lib/sendf.c
    lib/setopt.c
    lib/sha256.c
    lib/share.c
    lib/slist.c
    lib/smb.c
    lib/smtp.c
    lib/socketpair.c
    lib/socks.c
    lib/socks_gssapi.c
    lib/socks_sspi.c
    lib/speedcheck.c
    lib/splay.c
    lib/strcase.c
    lib/strdup.c
    lib/strerror.c
    lib/strtok.c
    lib/strtoofft.c
    lib/system_win32.c
    lib/telnet.c
    lib/tftp.c
    lib/timediff.c
    lib/timeval.c
    lib/transfer.c
    lib/url.c
    lib/urlapi.c
    lib/vauth/cleartext.c
    lib/vauth/cram.c
    lib/vauth/digest.c
    lib/vauth/digest_sspi.c
    lib/vauth/gsasl.c
    lib/vauth/krb5_gssapi.c
    lib/vauth/krb5_sspi.c
    lib/vauth/ntlm.c
    lib/vauth/ntlm_sspi.c
    lib/vauth/oauth2.c
    lib/vauth/spnego_gssapi.c
    lib/vauth/spnego_sspi.c
    lib/vauth/vauth.c
    lib/version.c
    lib/version_win32.c
    lib/vquic/curl_msh3.c
    lib/vquic/curl_ngtcp2.c
    lib/vquic/curl_quiche.c
    lib/vquic/vquic.c
    lib/vssh/libssh.c
    lib/vssh/libssh2.c
    lib/vssh/wolfssh.c
    lib/vtls/bearssl.c
    lib/vtls/hostcheck.c
    lib/vtls/keylog.c
    lib/vtls/mbedtls_threadlock.c
    lib/vtls/openssl.c
    lib/vtls/rustls.c
    lib/vtls/sectransp.c
    lib/vtls/vtls.c
    lib/vtls/wolfssl.c
    lib/vtls/x509asn1.c
    lib/warnless.c
    lib/ws.c
)

END()

RECURSE(
    bin
)