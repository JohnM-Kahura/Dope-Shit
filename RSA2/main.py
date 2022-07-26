from js import console
import rsa

def encrypt(*args, **kwargs):

    #print('args:', args)
    #print('kwargs:', kwargs)

    console.log(f'args: {args}')
    console.log(f'kwargs: {kwargs}')
    
    text = Element('exampleFormControlTextarea1').element.value

    publicKey, privateKey = rsa.newkeys(512)
    message=text
    encryptedMessage=rsa.encrypt(message.encode(),publicKey)

    Element('test-output').element.innerText = encryptedMessage

    #The decryption process is done below
    input_text = Element('decrypt_message').element.value
    decoded_message=rsa.decrypt(encryptedMessage,privateKey).decode()
    print(decoded_message)
    Element('decrypt-output').element.innerText = decoded_message  