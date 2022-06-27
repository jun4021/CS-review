# CNN - MNIST

## 목표 
- MNIST dataset을 주어진 CNN 모델을 이용하여 학습하기
-----------
## Training Setup
- MNIST dataset (60,000 training images, 10,000 test images)
- 30 epochs
- Adam optimizer
- Negative log likelihood loss
## Model 1

```python
model1=nn.Sequential(nn.Conv2d(in_channels=1,out_channels=32,stride=1,padding=1,kernel_size=3),
                    nn.ReLU(),          
                    nn.Conv2d(in_channels=32,out_channels=64,stride=1,padding=1,kernel_size=3), 
                    nn.ReLU(),          
                    nn.MaxPool2d(kernel_size=2),
                    nn.Flatten(),
                    nn.Linear(12544,64), 
                    nn.ReLU(),
                    nn.Linear(64,10),
                    nn.LogSoftmax(dim=1) 

                  ) 

```
## Model 2
```python
model2=nn.Sequential(nn.Conv2d(in_channels=1,out_channels=8,stride=1,padding=1,kernel_size=3),
                    nn.ReLU(),          
                    nn.Conv2d(in_channels=8,out_channels=16,stride=1,padding=1,kernel_size=3), 
                    nn.ReLU(),          
                    nn.MaxPool2d(kernel_size=2),
                    nn.Conv2d(in_channels=16,out_channels=32,stride=1,padding=1,kernel_size=3), 
                    nn.ReLU(),
                    nn.Conv2d(in_channels=32,out_channels=64,stride=1,padding=1,kernel_size=3), 
                    nn.ReLU(),
                    nn.MaxPool2d(kernel_size=2),
                    nn.Flatten(),
                    nn.Linear(64*7*7,64), 
                    nn.ReLU(),
                    nn.Linear(64,10),
                    nn.LogSoftmax(dim=1) 

                  ) 
```

## Model 3
- Conv - ReLu - Residual Block 1,2 - Max Pooling - FC - ReLu - FC - Log Softmax
```python
class Residual_Block(nn.Module):
    def __init__(self, dim):
        super(Residual_Block,self).__init__()
        # Residual Block
        self.residual_block = nn.Sequential(
                nn.Conv2d(dim, dim, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.Conv2d(dim, dim, kernel_size=3, padding=1),
            )            
        self.relu = nn.ReLU()
                  
    def forward(self, x):
        out = self. residual_block(x)  # F(x)
        out = out + x  # F(x) + x
        out = self.relu(out)
        return out
```
```python
class model3(nn.Module):
    def __init__(self):
        super(model3, self).__init__()
        self.conv1 = nn.Conv2d(1, 32, kernel_size=3, padding=1)
        self.relu = nn.ReLU()
        self.residual = Residual_Block(32)
        self.after =  nn.Sequential(nn.MaxPool2d(kernel_size=2),
                    nn.Flatten(),
                    nn.Linear(6272,64), 
                    nn.ReLU(),
                    nn.Linear(64,10),
                    nn.LogSoftmax(dim=1))
    def forward(self, x):
        x = self.conv1(x)
        x = self.relu(x)
        x = self.residual(x)
        x = self.residual(x)
        output = self.after(x)
        
        return output
```

## Train
```python
def train(num,model,trainloader,testloader):   
    epochs = 30 # total number of iteration for training
    running_loss_list= []
    test_acc_list =[]
    epochs_list = []
    optimizer = optim.Adam(model.parameters())
    criterion = nn.NLLLoss()

    for e in range(epochs):
        running_loss = 0
        for images, labels in trainloader:

            # defining gradient in each epoch as 0
            optimizer.zero_grad()
            
            # modeling for each image batch
            output = model(images)
            
            # calculating the loss
            loss = criterion(output, labels)
            
            # This is where the model learns by backpropagating
            loss.backward()
            
            # And optimizes its weights here
            optimizer.step()
            
            # calculating the loss
            running_loss += loss.item()
            
        else:
            print("Epoch {} - Training loss: {}".format(e, running_loss/len(trainloader)))
            
            running_loss_list.append(running_loss/len(trainloader))
            test_acc_list.append(test(model,testloader))



    # Save model
    torch.save(model, 'model'+ num +'.pt')
    print(running_loss_list)
    print(test_acc_list)
    return running_loss_list, test_acc_list
```

## Test
```python
def test(model,test_loader):
    model.eval()
    correct = 0
    for data, target in test_loader:
        with torch.no_grad():
            output = model(data)    
        prediction = output.data.max(1)[1]
        correct += prediction.eq(target.data).sum()
        
    print('\nTest set: Accuracy: {:.2f}%'.format(100. * correct / len(test_loader.dataset)))
    return (correct / len(test_loader.dataset)).item()
```
## Result
- Model1

![image](https://user-images.githubusercontent.com/86395683/175861618-648b0f41-2335-4da1-b216-1db7d22888db.png)
![image](https://user-images.githubusercontent.com/86395683/175861627-220daf9c-058d-44d0-be28-de9f9c819862.png)
- Model2

![image](https://user-images.githubusercontent.com/86395683/175861637-d9020be3-6ea4-4776-922d-3df37dd5c322.png)
![image](https://user-images.githubusercontent.com/86395683/175861639-522f861d-d579-452b-8fe2-f280ec12068d.png)
- Model3

![image](https://user-images.githubusercontent.com/86395683/175861647-761d0732-1353-44d8-8ca6-ade7e3ab36c1.png)
![image](https://user-images.githubusercontent.com/86395683/175861652-634cab59-cf9e-4dec-ab8d-82eedc6de7c7.png)
