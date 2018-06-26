type TCorpse = record
  Id: Cardinal;
  X,Y: Word;
  Z: ShortInt;
  Carved: Boolean;
  Looted: Boolean;
  Discovered: Int64;
  NextTry: int64;
end;

function GetCorpse(Idx: Integer): TCorpse;
begin
  Result.Id := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_Id');
  Result.X := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_X');
  Result.Y := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_Y');
  Result.Z := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_Z');
  Result.Carved := GetGlobalBool('Corpses_'+IntToStr(Idx)+'_Carved');
  Result.Looted := GetGlobalBool('Corpses_'+IntToStr(Idx)+'_Looted');
  Result.Discovered := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_Discovered');
  Result.NextTry := GetGlobalInt('Corpses_'+IntToStr(Idx)+'_NextTry');
end;

procedure SetCorpse(Idx: Integer; const Corpse: TCorpse);
begin
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_Id', Corpse.Id);
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_X', Corpse.X);
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_Y', Corpse.Y);
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_Z', Corpse.Z);
  SetGlobalBool('Corpses_'+IntToStr(Idx)+'_Carved', Corpse.Carved);
  SetGlobalBool('Corpses_'+IntToStr(Idx)+'_Looted', Corpse.Looted);
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_Discovered', Corpse.Discovered);
  SetGlobalInt('Corpses_'+IntToStr(Idx)+'_NextTry', Corpse.NextTry);
end;

function IndexCorpse(Id: Cardinal): Integer;
var i, L: Integer;
begin
  L := GetGlobalInt('Corpses_Length');
  Result := -1;
  for i := 0 to L-1 do begin
    if GetGlobalInt('Corpses_'+IntToStr(i)+'_Id') = Id then
    begin
      Result := i;
      Break;
    end;
  end;
end;

procedure AddCorpse(Id: Cardinal);
var i, L: Integer;
begin
  L := GetGlobalInt('Corpses_Length');
  for i := 0 to L-1 do if GetGlobalInt('Corpses_'+IntToStr(i)+'_Id') = Id then Exit;
  SetGlobalInt('Corpses_Length', L+1);
  SetGlobalInt('Corpses_'+IntToStr(L)+'_Id', Id);
  SetGlobalInt('Corpses_'+IntToStr(L)+'_X', GetX(Id));
  SetGlobalInt('Corpses_'+IntToStr(L)+'_Y', GetY(Id));
  SetGlobalInt('Corpses_'+IntToStr(L)+'_Z', GetZ(Id));
  SetGlobalBool('Corpses_'+IntToStr(L)+'_Carved', False);
  SetGlobalBool('Corpses_'+IntToStr(L)+'_Looted', False);
  SetGlobalInt('Corpses_'+IntToStr(L)+'_Discovered', Clock);
  SetGlobalInt('Corpses_'+IntToStr(L)+'_NextTry', 0);
end;

procedure DeleteCorpse(Idx: Integer);
var L: Imnteger;
begin
  L := GetGlobalInt('Corpses_Length');
  if (0 <= Idx) and (Idx < L) then begin
    if (Idx+1 < L) and (L > 1) then for i := Idx to L-2 do SetCorpse(i, GetCorpse(i+1));
    SetGlobalInt('Corpses_Length', L-1);
  end;
end;

const TimeoutExpireCorpse = 1000*60*15;

procedure ExpireCorpses;
begin
  i := 0;
  while (i < GetGlobalInt('Corpses_Length')) do begin
    if (GetCorpse(i).Discovered+TimeoutExpireCorpse < Clock) then begin
      DeleteCorpse(i);
    end else begin
      i := i + 1;
    end;
  end;
end;

function ClosestCorpseIndex: Integer;
var i, L, tD, D: Integer; C: TCorpse;
begin
  ExpireCorpses;
  L := GetGlobalInt('Corpses_Length');
  Result := -1;
  D := High(D);
  for i := 0 to L-1 do begin
    C := GetCorpse(i);
    tD := Dist(MyX, MyY, C.X, C.Y);
    if tD < D then begin
      Result := i;
      D := tD;
    end;
  end;
end;

function CarveCorpse(Id: Cardinal): Boolean;
begin

end;


